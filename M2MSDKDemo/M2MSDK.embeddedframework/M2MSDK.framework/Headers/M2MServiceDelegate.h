//
//  M2MServiceDelegate.h
//  M2MSDK
//
//  Created by Z on 10/1/15.
//  Copyright © 2015 Inmarket llc. All rights reserved.
//
#import "M2MConfig.h"

typedef enum {
    M2M_REQUEST_INIT = 0,
    M2M_REQUEST_CHECKIN_PLACES,
    M2M_REQUEST_MANUAL_CHECKIN,
    M2M_REQUEST_DEBUG_REQUEST,
    M2M_REQUEST_OTHERS
} M2M_REQUEST_TYPE;

typedef enum {
    M2M_NO_LOCATION_PERMISSION_ERROR_CODE   = -11,
    M2M_NOT_INITIALIZED_ERROR_CODE          = -98,
    M2M_NO_STATUS_ERROR_CODE                = -99,
    M2M_UNKNOWN_ERROR_CODE                  = -100,
    M2M_TIME_OUT_ERROR_CODE                 = -110,
    M2M_PENDING_CHECKIN_OPPS_ERROR_CODE     = -221,
    M2M_PENDING_CHECKIN_ERROR_CODE          = -222, 
    M2M_NO_ADS_AVAILABLE_ERROR_CODE         = -311,
    M2M_ENGAGEMENT_EXPIRED_ERROR_CODE       = -400
} M2M_ERROR_CODES;

/**
 * The M2M SDK's delegate. Implement this protocol to receive SDK updates
 */
@protocol M2MServiceDelegate <NSObject>

@optional


/**
 * This method is called when M2M makes a decision around the user. 
 * M2M returns some additional data around that decision for you
 * @param dict the dictionary containing some of M2M's decision data
 */
-(void)onM2mDecisionWithData:(NSDictionary*)dict;


/**
 * This method is called when M2M is Showing an Engagement
 */
-(void)didShowEngagement;


/**
 * This method is called when M2M engagement is dismissed
 */
-(void)didDismissEngagement;

/**
 * Called when M2M has an engagement ready for viewing.
 * If waitForReady is set on M2MBeaconMonitor,
 * then the app must call [M2MBeaconMonitor readyForEngagement]
 * after this method is called, in order to receive the interstitial.
 *
 * This method is called in the background.
 */
-(void)didReceiveEngagement;

/**
 * This method is called when M2M runs into an error. This method replaces the  -(void)onM2mServiceConfig:(M2MConfig*)config  withCode:(int)code  andMessage:(NSString*)message;
 * @param code the ineteger code for error
 * @param message the message the SDK returns along with the error code
 * @param to inform the user that the error happened with what type of request
 */
-(void)onErrorWithCode:(M2M_ERROR_CODES)code andMessage:(NSString*)message forRequest:(M2M_REQUEST_TYPE)type;


/**
 * This method is called when M2M Checkin runs into an error.
 * @param code the ineteger code for error
 * @param message the message the SDK returns along with the error code
 */
-(void)checkInDidFailWithCode:(M2M_ERROR_CODES)code andMessage:(NSString*)message;


/**
 * This method is called when M2M there are CheckinOpportunities available
 * @param opps Json string of available Opps 
 */
-(void)didGetAvailableOpps:(NSDictionary*)opps;

/**
 * This method provides info on the  detected beacons, when publisher owned beacons are detected by the client, and
 * whether or not the detection resulted in a push message
 * @param NSDictionary of beacons detected.
 * Sample NSDictionary for beacons detected:
 * <code>{<br/>
 *      <br/>"push_sent"= 1,
 *      <br/>"data"= [{
 *          <br/>"addr"= "1352 Abbott Kinney Blvd",
 *          <br/>"city"= "Venice",
 *          <br/>"state"= "CA",
 *          <br/>"ibeacon_id"= "1350",
 *          <br/>"partner_id": "12345"
 *          <br/>}]
 *       <br/>}
 * </code>
 */
-(void)didReceiveDetection:(NSDictionary*)detection;

@end
