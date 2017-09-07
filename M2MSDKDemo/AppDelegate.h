//
//  AppDelegate.h
//  M2MSDKDemo
//
//  Created by Водолазкий В.В. on 07.09.17.
//  Copyright © 2017 Geomatix Laboratory S.R.O. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (readonly, strong) NSPersistentContainer *persistentContainer;

- (void)saveContext;


@end

