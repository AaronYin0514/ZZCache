//
//  ZZCache.h
//  ZZCache
//
//  Created by apple on 16/5/29.
//  Copyright © 2016年 EXComing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZZDiskCache.h"
#import "ZZMemoryCache.h"

@class ZZCache;
typedef void(^ZZCacheBlock)(ZZCache *cache);
typedef void(^ZZCacheObjectBlock)(ZZCache *cache, NSString *key, id object);

@interface ZZCache : NSObject

#pragma mark - Core

@property (readonly) NSString *name;

@property (readonly) dispatch_queue_t queue;

@property (readonly) NSUInteger diskByteCount;

@property (readonly) ZZDiskCache *diskCache;

@property (readonly) ZZMemoryCache *memoryCache;

#pragma mark - Initialization

+(instancetype)sharedCache;

-(instancetype)initWithName:(NSString *)name;

-(instancetype)initWithName:(NSString *)name rootPath:(NSString *)rootPath;
#pragma mark - Asynchronous Methods

-(void)objectForKey:(NSString *)key block:(ZZCacheObjectBlock)block;

-(void)setObject:(id <NSCopying>)object forKey:(NSString *)key block:(ZZCacheObjectBlock)block;

-(void)removeObjectForKey:(NSString *)key block:(ZZCacheObjectBlock)block;

-(void)trimToDate:(NSDate *)date block:(ZZCacheBlock)block;

-(void)removeAllObjects:(ZZCacheBlock)block;

#pragma mark - Synchronous Methods

-(void)objectForKey:(NSString *)key;

-(void)setObject:(id <NSCopying>)object forKey:(NSString *)key;

-(void)removeObjectForKey:(NSString *)key;

-(void)trimToDate:(NSDate *)date;

-(void)removeAllObjects;

@end
