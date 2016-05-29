//
//  ZZCache.m
//  ZZCache
//
//  Created by apple on 16/5/29.
//  Copyright © 2016年 EXComing. All rights reserved.
//

#import "ZZCache.h"

NSString * const ZZCachePrefix = @"com.excoming.ZZCache";
NSString * const ZZCacheSharedName = @"ZZCacheShared";

@interface ZZCache ()

#if OS_OBJECT_USE_OBJC
@property (strong, nonatomic) dispatch_queue_t quque;
#else
@property (assign, nonatomic) dispatch_queue_t queue;
#endif

@end

@implementation ZZCache

#if !OS_OBJECT_USE_OBJC
-(void)dealloc {
    dispatch_release(_queue);
    _queue = nil;
}
#endif

#pragma mark - Initialization -
-(instancetype)initWithName:(NSString *)name {
    return [self initWithName:name rootPath:[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0]];
}

-(instancetype)initWithName:(NSString *)name rootPath:(NSString *)rootPath {
    if (!name.length) {
        return nil;
    }
    if (self = [super init]) {
        _name = [name copy];
        NSString *queueName = [NSString stringWithFormat:@"%@.%p", ZZCacheSharedName, self];
        _queue = dispatch_queue_create([queueName UTF8String], DISPATCH_QUEUE_CONCURRENT);
        _diskCache = [[ZZDiskCache alloc] initWithName:_name rootPath:rootPath];
        _memoryCache = [[ZZMemoryCache alloc] init];
    }
    return self;
}

-(NSString *)description {
    return [NSString stringWithFormat:@"%@.%@.%p", ZZCachePrefix, _name, self];
}

+(instancetype)sharedCache {
    static id cache;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        cache = [[self alloc] initWithName:ZZCacheSharedName];
    });
    return cache;
}

#pragma mark - Public Asynchronous Methods -
-(void)objectForKey:(NSString *)key block:(ZZCacheObjectBlock)block {
    if (!key || !block) {
        return;
    }
    __weak ZZCache *weakSelf = self;
    dispatch_async(_queue, ^{
        ZZCache *strongSelf = weakSelf;
        if (!strongSelf) {
            return;
        }
        __weak ZZCache *weakSelf = strongSelf;
        [strongSelf -> _memoryCache objectForKey:key block:^(ZZMemoryCache *cache, NSString *key, id object) {
            ZZCache *strongSelf = weakSelf;
            if (!strongSelf) {
                return;
            }
            if (object) {
                [strongSelf -> _diskCache fileURLForKey:key block:^(ZZDiskCache *cache, NSString *key, id<NSCopying> object, NSURL *fileURL) {
                    // update the access time on disk
                }];
                __weak ZZCache *weakSelf = strongSelf;
                dispatch_async(strongSelf -> _queue, ^{
                    ZZCache *strongSelf = weakSelf;
                    if (strongSelf) {
                        block(strongSelf, key, object);
                    }
                });
            } else {
                __weak ZZCache *weakSelf = strongSelf;
                [strongSelf -> _diskCache objectForKey:key block:^(ZZDiskCache *cache, NSString *key, id<NSCopying> object, NSURL *fileURL) {
                    ZZCache *strongSelf = weakSelf;
                    if (!strongSelf) {
                        return;
                    }
                    [strongSelf -> _memoryCache setObject:object forKey:key block:nil];
                    
                    __weak ZZCache *weakSelf = strongSelf;
                    dispatch_async(strongSelf -> _queue, ^{
                        ZZCache *strongSelf = weakSelf;
                        if (strongSelf) {
                            block(strongSelf, key, object);
                        }
                    });
                }];
            }
        }];
    });
}

-(void)setObject:(id<NSCopying>)object forKey:(NSString *)key block:(ZZCacheObjectBlock)block {
    if (!key || !object) {
        return;
    }
    dispatch_group_t group = nil;
    ZZMemoryCacheObjectBlock memoryCacheObjectBlock = nil;
    ZZDiskCacheObjectBlock diskCacheObjectBlock = nil;
    
}

#pragma mark - Public Synchronous Accessors -

#pragma mark - Public Synchronous Methods -

@end
