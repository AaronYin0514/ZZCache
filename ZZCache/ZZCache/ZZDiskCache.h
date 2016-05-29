//
//  ZZDiskCache.h
//  ZZCache
//
//  Created by apple on 16/5/29.
//  Copyright © 2016年 EXComing. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ZZDiskCache;
typedef void(^ZZDiskCacheBlock)(ZZDiskCache *cache);
typedef void(^ZZDiskCacheObjectBlock)(ZZDiskCache *cache, NSString *key, id <NSCopying> object, NSURL *fileURL);

@protocol TMCacheBackgroundTaskManager;

@interface ZZDiskCache : NSObject

#pragma mark - Core

@property (readonly) NSString *name;

@property (readonly) NSURL *cacheURL;

@property (readonly) NSUInteger byteCount;

@property (assign) NSUInteger byteLimit;

@property (assign) NSTimeInterval ageLimit;

#pragma mark - Event Blocks

@property (copy) ZZDiskCacheObjectBlock willAddObjectBlock;

@property (copy) ZZDiskCacheObjectBlock willRemoveObjectBlock;

@property (copy) ZZDiskCacheBlock willRemoveAllObjectsBlock;

@property (copy) ZZDiskCacheObjectBlock didAddObjectBlock;

@property (copy) ZZDiskCacheObjectBlock didRemoveObjectBlock;

@property (copy) ZZDiskCacheBlock didRemoveAllObjectsBlock;

#pragma mark - Initialization

+(instancetype)sharedCache;

+(instancetype)sharedQueue;

+(void)emptyTrash;

-(instancetype)initWithName:(NSString *)name;

-(instancetype)initWithName:(NSString *)name rootPath:(NSString *)rootPath;

#pragma mark - Asynchronous Methods

-(void)objectForKey:(NSString *)key block:(ZZDiskCacheObjectBlock)block;

-(void)fileURLForKey:(NSString *)key block:(ZZDiskCacheObjectBlock)block;

-(void)setObject:(id <NSCopying>)object forKey:(NSString *)key block:(ZZDiskCacheObjectBlock)block;

-(void)removeObjectForKey:(NSString *)key block:(ZZDiskCacheObjectBlock)block;

-(void)trimToDate:(NSDate *)date block:(ZZDiskCacheBlock)block;

-(void)trimToSize:(NSUInteger)byteCount block:(ZZDiskCacheBlock)block;

-(void)trimToSizeByDate:(NSUInteger)byteCount block:(ZZDiskCacheBlock)block;

-(void)removeAllObjects:(ZZDiskCacheBlock)block;

- (void)enumerateObjectsWithBlock:(ZZDiskCacheObjectBlock)block completionBlock:(ZZDiskCacheBlock)completionBlock;

#pragma mark - Synchronous Methods

-(id <NSCopying>)objectForKey:(NSString *)key;

-(NSURL *)fileURLForKey:(NSString *)key;

-(void)setObject:(id <NSCopying>)object forKey:(NSString *)key;

-(void)removeObjectForKey:(NSString *)key;

#pragma mark - Background Tasks

+(void)setBackgroundTaskManager:(id <TMCacheBackgroundTaskManager>)backgroundTaskManager;

@end
