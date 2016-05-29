//
//  ZZMemoryCache.h
//  ZZCache
//
//  Created by apple on 16/5/29.
//  Copyright © 2016年 EXComing. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ZZMemoryCache;

typedef void (^ZZMemoryCacheBlock)(ZZMemoryCache *cache);
typedef void (^ZZMemoryCacheObjectBlock)(ZZMemoryCache *cache, NSString *key, id object);

@interface ZZMemoryCache : NSObject

#pragma mark - Core

@property (readonly) dispatch_queue_t queue;

@property (readonly) NSUInteger totalCost;

@property (assign) NSUInteger costLimit;

@property (assign) NSTimeInterval ageLimit;

@property (assign) BOOL removeAllObjectsOnMemoryWarning;

@property (assign) BOOL removeAllObjectsOnEnteringBackground;

#pragma mark - Event Blocks

@property (copy) ZZMemoryCacheObjectBlock willAddObjectBlock;

@property (copy) ZZMemoryCacheObjectBlock willRemoveObjectBlock;

@property (copy) ZZMemoryCacheBlock willRemoveAllObjectsBlock;

@property (copy) ZZMemoryCacheObjectBlock didAddObjectBlock;

@property (copy) ZZMemoryCacheObjectBlock didRemoveObjecBlock;

@property (copy) ZZMemoryCacheBlock didRemoveAllObjectsBlock;

@property (copy) ZZMemoryCacheBlock didReceiveMemoryWarningBlock;

@property (copy) ZZMemoryCacheBlock didEnterBackgroundBlock;

#pragma mark - Shared Cache

+(instancetype)sharedCache;

#pragma mark - Asynchronous Methods

-(void)objectForKey:(NSString *)key block:(ZZMemoryCacheObjectBlock)block;

-(void)setObject:(id)object forKey:(NSString *)key block:(ZZMemoryCacheObjectBlock)block;

-(void)setObject:(id)object forKey:(NSString *)key withCost:(NSUInteger)cost block:(ZZMemoryCacheObjectBlock)block;

-(void)removeObjectForKey:(NSString *)key block:(ZZMemoryCacheObjectBlock)block;

-(void)trimToDate:(NSDate *)date block:(ZZMemoryCacheBlock)block;

-(void)trimToCost:(NSUInteger)cost block:(ZZMemoryCacheBlock)block;

-(void)trimToCostByDate:(NSUInteger)cost block:(ZZMemoryCacheBlock)block;

-(void)removeAllObjects:(ZZMemoryCacheBlock)block;

-(void)enumerateObjectsWithBlock:(ZZMemoryCacheObjectBlock)block completionBlock:(ZZMemoryCacheBlock)completionBlock;

#pragma mark - Synchronous Methods

-(id)objectForKey:(NSString *)key;

-(void)setObject:(id)object forKey:(NSString *)key;

-(void)setObject:(id)object forKey:(NSString *)key withCost:(NSUInteger)cost;

-(void)removeObjectForKey:(NSString *)key;

-(void)trimToDate:(NSDate *)date;

-(void)trimToCost:(NSUInteger)cost;

-(void)trimToCostByDate:(NSUInteger)cost;

-(void)removeAllObjects;

-(void)enumerateObjectsWithBlock:(ZZMemoryCacheObjectBlock)block;

@end
