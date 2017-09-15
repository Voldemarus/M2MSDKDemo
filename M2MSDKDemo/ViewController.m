//
//  ViewController.m
//  M2MSDKDemo
//
//  Created by Водолазкий В.В. on 07.09.17.
//  Copyright © 2017 Geomatix Laboratory S.R.O. All rights reserved.
//

#import "ViewController.h"
#import <M2MSDK/M2MBeaconMonitor.h>

#import "Constants.h"

@interface ViewController () <M2MServiceDelegate>

@property (weak, nonatomic) IBOutlet UIButton *initializingButton;
@property (weak, nonatomic) IBOutlet UIImageView *sdkInitIndicator;

@property (weak, nonatomic) IBOutlet UIView *configurationView;
@property (weak, nonatomic) IBOutlet UILabel *pushOptedStatus;
@property (weak, nonatomic) IBOutlet UILabel *geofencingStatus;
@property (weak, nonatomic) IBOutlet UILabel *stoppedStatus;


- (IBAction)initializationButtonClicked:(id)sender;

@end

@implementation ViewController

- (void)viewDidLoad {
	[super viewDidLoad];
	
	CALayer *l = self.initializingButton.layer;
	l.borderWidth = 1.5;
	l.borderColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.88 alpha:1.0].CGColor;
	l.cornerRadius = 9.0;
	l.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.44 alpha:1.0].CGColor;
	self.initializingButton.titleLabel.textColor = [UIColor whiteColor];
	self.initializingButton.tintColor = [UIColor whiteColor];
	self.initializingButton.titleLabel.font = [UIFont systemFontOfSize:22.0 weight:0.75];
	
	self.sdkInitIndicator.alpha = 0.0;
	l = self.configurationView.layer;
	l.borderColor = [UIColor greenColor].CGColor;
	l.cornerRadius = 5.0;
	self.configurationView.alpha = 0;
	
}


- (void)didReceiveMemoryWarning {
	[super didReceiveMemoryWarning];
	// Dispose of any resources that can be recreated.
}


- (IBAction)initializationButtonClicked:(id)sender
{
	[M2MBeaconMonitor initWithApplicationUuid:APPLICATION_UUID andDelegate:self];
	[M2MBeaconMonitor startMonitoringWithDelegate:self];
	[M2MBeaconMonitor sharedInstance].userId = USER_ID;
	
//	[M2MBeaconMonitor sharedInstance].optInForGeofencing = NO;
//	[M2MBeaconMonitor updateServiceWithDelegate:self];
	
	M2MConfig *config = [M2MBeaconMonitor getM2MConfig];
	
	self.pushOptedStatus.text = (config.isOptedInForPush ? @"YES" : @"NO");
	self.geofencingStatus.text = (config.isOptedInForGeofencing ? @"YES" : @"NO");
	self.stoppedStatus.text = (config.isStopped ? @"YES" : @"NO");
	
	self.configurationView.alpha = 1.0;
	
	
}

#pragma mark - M2MServiceDelegate delegate methods -

-(void)onErrorWithCode:(M2M_ERROR_CODES)code andMessage:(NSString*)message forRequest:(M2M_REQUEST_TYPE)type
{
	NSLog(@"error code - %d  message - %@ request - %u",
		  code, message, type);
}

-(void)checkInDidFailWithCode:(M2M_ERROR_CODES)code andMessage:(NSString*)message
{
	NSLog(@"errCode - %d message - %@",code, message);
}

-(void)didGetAvailableOpps:(NSDictionary*)opps
{
	NSLog(@"opps = %@",opps);
}


-(void)onM2mDecisionWithData:(NSDictionary*)dict
{
	NSLog(@"Decision data - %@",dict);
}

- (BOOL) respondsToSelector:(SEL)aSelector
{
	NSString *methodName = NSStringFromSelector(aSelector);
	NSLog(@">>> respondsToSelector:%@",methodName);
	return [super respondsToSelector:aSelector];
}

@end
