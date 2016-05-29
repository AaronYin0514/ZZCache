//
//  ZZCacheBackgroundTaskManager.h
//  ZZCache
//
//  Created by apple on 16/5/29.
//  Copyright © 2016年 EXComing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol ZZCacheBackgroundTaskManager <NSObject>

- (UIBackgroundTaskIdentifier)beginBackgroundTask;

- (void)endBackgroundTask:(UIBackgroundTaskIdentifier)identifier;

@end
