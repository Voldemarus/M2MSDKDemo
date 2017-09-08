//
//  BeaconMonitor.h
//  BeaconMonitor
//
//  Created by nithyasriram on 1/17/14.
//  Copyright (c) 2014 Inmarket llc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreLocation/CLBeaconRegion.h>
#import "M2MConfig.h"
#import "M2MServiceDelegate.h"

//M2MBeaconMonitor class
@interface M2MBeaconMonitor : NSObject

/**
 * Your user's ID to help with reporting. Optional.
 * This is sent to inMarket servers each time the application is
 * foregrounded, along with your company's assigned publisher id.
 * Changes will take effect on the next foregrounding of the app.
 */
@property(copy) NSString *userId;

/**
 * flag for enabling and disabling Geofencing
 * defaults to `YES`
 */
@property(nonatomic)BOOL                    optInForGeofencing;


/**
 * The singleton instance of the M2MBeaconMonitor. Make sure to use this for all access
 * @return the instance
 */
+(M2MBeaconMonitor *)sharedInstance;

/**
 * M2M SDK Initializer. Should be called in `application:didFinishLaunchingWithOptions:`
 * @param publisherId your publisher ID provided by your inMarket account manager
 * @param delegate your delegate to receive updates from the m2m sdk
 */
+(void)initWithApplicationUuid:(NSString*)applicationUuid andDelegate:(id<M2MServiceDelegate>)delegate;

/**
 * Update's M2M with the users push token for remote pushes
 * @param data the user's push token data
 */
+(void)setDeviceTokenData:(NSData*)data;

/**
 * Call this in your application's `didReceiveRemoteNotification:withCompletionHandler`
 * If this method returns true, it means the notification is from M2M and M2M properly handled your remote notification. You should return from the `didReceiveRemoteNotification` method when this returns true
 * If this method returns false, it means the notification is not from M2M and you should proceed to handle the remote notification payload
 * @param userInfo the userInfo dictionary provided by the applications didReceiveRemoteNotification method
 * @param userInfo the completionHandler provided the applications didReceiveRemoteNotification method
 * @return whether or not the sdk handled the notification
 * **Note:**
 * You must call this method in `didReceiveRemoteNotification:withCompletionHandler` and **not** `didReceiveRemoteNotification` (without the handler)
 */
+(BOOL)handlePushNotification:(NSDictionary*)userInfo withCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler;

/**
 * Call this to start the M2M SDK's monitoring service
 * @param delegate the delegate to receive SDK updates with
 **/
+(void)startMonitoringWithDelegate:(id<M2MServiceDelegate>)delegate;

/**
 * Call this after changed the M2M SDK's configuration
 * @param delegate the delegate to receive SDK updates with
 **/
+(void)updateServiceWithDelegate:(id<M2MServiceDelegate>)delegate;

/**
 * The configuration the current M2M SDK is configured with
 * @return the config
 */
+(M2MConfig*)getM2MConfig;

/**
 *  Call this when you want to stop the M2M SDK
 *  A good time to do this is when the user logs out of your app
 *  M2M will not make any push notifications until startService is called again
 */
+(void)stopService;

/**
 * Provide tag keywords in order to provide more relevant interstitial ads
 * @param tags the dictionary containing keywords for your application
 */
+(void)setTagKeyWords:(NSDictionary*)tags;

/**
 * the tag dictionary provided by your application
 * @return the dictionary
 */
+(NSDictionary*)getTagKeywords;

/**
 * The current version of the sdk
 * @return the version
 */
+(NSString*)getVersionNum;



/**
 * Get the List Opportunities where user can checkin
 */
+(void)getAvailableOpps:(id<M2MServiceDelegate>)delegate;


/**
 * Manual Checkin to Location
 * @param Place Id of the Location to be Checked into
 * @param delegate the delegate to receive SDK updates with
 */
+(void)checkInToOpp:(NSString*)placeId withDelegate:(id<M2MServiceDelegate>)delegate;

/**
 * Set to true if you want to explicitly notify the sdk
 * when your application is ready to display each interstitial.
 */
+(void)setWaitForReady:(BOOL)wait;

/**
 * Must be called, when waitForReady is YES,
 * after the delegate method didReceiveEngagement
 * is called
 */
+(void)readyForEngagement;

/**
 * true if we have an interstitial ready for display.
 * Use this when coming in from the background,
 * to determine whether to call readyForEngagement
 */
+(BOOL)isEngagementReady;

@end
