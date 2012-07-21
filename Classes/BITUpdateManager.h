/*
 * Author: Andreas Linde <mail@andreaslinde.de>
 *         Peter Steinberger
 *
 * Copyright (c) 2012 HockeyApp, Bit Stadium GmbH.
 * Copyright (c) 2011 Andreas Linde.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


#import <UIKit/UIKit.h>


typedef enum {
	BITUpdateComparisonResultDifferent,
	BITUpdateComparisonResultGreater
} BITUpdateComparisonResult;

typedef enum {
	BITUpdateAuthorizationDenied,
	BITUpdateAuthorizationAllowed,
	BITUpdateAuthorizationPending
} BITUpdateAuthorizationState;

typedef enum {
  BITUpdateCheckStartup = 0,
  BITUpdateCheckDaily = 1,
  BITUpdateCheckManually = 2
} BITUpdateSetting;

@protocol BITUpdateManagerDelegate;

@class BITAppVersionMetaInfo;
@class BITUpdateViewController;

@interface BITUpdateManager : NSObject <UIAlertViewDelegate> {
@private
  NSString *_appIdentifier;
  NSString *_currentAppVersion;
  
  UINavigationController *_navController;
  BITUpdateViewController *_currentHockeyViewController;
  
  BOOL _dataFound;
  BOOL _showFeedback;
  BOOL _updateAlertShowing;
  BOOL _lastCheckFailed;
  
  BOOL _isAppStoreEnvironment;
  
  NSString *_uuid;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Setting Properties

// delegate is optional
@property (nonatomic, assign) id <BITUpdateManagerDelegate> delegate;

// hockey secret is required if authentication is used
@property (nonatomic, retain) NSString *authenticationSecret;

// if YES, the current user data is send: device type, iOS version, app version, UDID (default)
// if NO, no such data is send to the server
@property (nonatomic, assign, getter=shouldSendUserData) BOOL sendUserData;

// if YES, the the users usage time of the app to the service, only in 1 minute granularity! (default)
// if NO, no such data is send to the server
@property (nonatomic, assign, getter=shouldSendUsageTime) BOOL sendUsageTime;

// if YES, the user agrees to send the usage data, user can change it if the developer shows the settings (default)
// if NO, the user overwrites the developer setting and no such data is sent
@property (nonatomic, assign, getter=isAllowUserToDisableSendData) BOOL allowUserToDisableSendData;

// if YES, the user allowed to send user data (default)
// if NO, the user denied to send user data
@property (nonatomic, assign, getter=doesUserAllowsSendUserData) BOOL userAllowsSendUserData;

// if YES, the user allowed to send usage data (default)
// if NO, the user denied to send usage data
@property (nonatomic, assign, getter=doesUserAllowsSendUsageTime) BOOL userAllowsSendUsageTime;

// if YES, the new version alert will be displayed always if the current version is outdated (default)
// if NO, the alert will be displayed only once for each new update
@property (nonatomic, assign) BOOL alwaysShowUpdateReminder;

// if YES, the user can change the HockeyUpdateSetting value (default)
// if NO, the user can not change it, and the default or developer defined value will be used
@property (nonatomic, assign, getter=shouldShowUserSettings) BOOL showUserSettings;

// set bar style of navigation controller
@property (nonatomic, assign) UIBarStyle barStyle;

// set modal presentation style of update view
@property (nonatomic, assign) UIModalPresentationStyle modalPresentationStyle;

// if YES, then an update check will be performed after the application becomes active (default)
// if NO, then the update check will not happen unless invoked explicitly
@property (nonatomic, assign, getter=isCheckForUpdateOnLaunch) BOOL checkForUpdateOnLaunch;

// if YES, the alert notifying about an new update also shows a button to install the update directly
// if NO, the alert notifying about an new update only shows ignore and show update button
@property (nonatomic, assign, getter=isShowingDirectInstallOption) BOOL showDirectInstallOption;

// if YES, each app version needs to be authorized by the server to run on this device
// if NO, each app version does not need to be authorized (default) 
@property (nonatomic, assign, getter=isRequireAuthorization) BOOL requireAuthorization;

// HockeyComparisonResultDifferent: alerts if the version on the server is different (default)
// HockeyComparisonResultGreater: alerts if the version on the server is greater
@property (nonatomic, assign) BITUpdateComparisonResult compareVersionType;

// see HockeyUpdateSetting-enum. Will be saved in user defaults.
// default value: HockeyUpdateCheckStartup
@property (nonatomic, assign) BITUpdateSetting updateSetting;

// convenience methode to create hockey view controller
- (BITUpdateViewController *)hockeyViewController:(BOOL)modal;

@end
