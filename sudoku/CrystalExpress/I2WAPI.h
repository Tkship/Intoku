/*!
 * @header I2WAPI.h
 *
 * @brief The interface for initializing CrystalExpress SDK and handle SDK life-cycle callbacks.
 *
 * @author Intowow
 * @copyright 2016 intowow. All rights reserved.
 * @version 2.0
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/* define milli-second */
typedef long long CEMilliSec;

@class ADView;

/*!
 *  @brief SDK Error Code
 */
typedef NS_ENUM(NSInteger, CEAdBlockReasonCode)
{
    /*! Reason Code for blockAd */
    CEAdBlockReasonNotRelevant,
    CEAdBlockReasonSeeAdTooOften,
    CEAdBlockReasonInappropriate,
    CEAdBlockReasonInvalidVideoAsset
};


typedef NS_ENUM(NSInteger, CEADErrorCode)
{
    CEADLoadErrorNone                            = 0,
    CEADLoadErrorNoADCandidate,
    CEADLoadErrorTimeout,
    CEADLoadErrorSDKNotReady,
    CEADLoadErrorNoADCreative,
    CEADLoadErrorNoADServing,
    CEADLoadErrorInvalidPlacement,
    CEADLoadErrorInvalidParameter,
    CEADLoadErrorRenderError,
    CEADLoadErrorInvalidThread,
};

/*!
 *  @brief AD Break Type
 */
typedef NS_ENUM (int, CEADBreakType) {
    CEADBreakTypeSingleAD = 1,
    CEADBreakTypeFixedTime,
    CEADBreakTypeMultiAD,
    CEADBreakTypeUnlimited
};


/*!
 *  @brief The AD more information
 */
@interface Ad : NSObject
/*! This property is AD unique string id */
@property (nonatomic, strong, readonly) NSString * campaignId;
/*! This property is the click landing url */
@property (nonatomic, strong, readonly) NSString * engageUrl;
@end

/*!
 *  @brief CrsytalExpress APP event delegate
 */
@protocol I2WAPPEventDelegate <NSObject>
@optional
/*!
 *  @brief callback when file download ended
 *
 *  @param downloadTraffic doanloaded size
 */
- (void) onDownloadTaskEnded:(NSNumber *) downloadTraffic;

@end

/*!
 *  @brief I2WAPI class
 */
@interface I2WAPI : NSObject
/*!
 *  @brief initializer of I2WAPI
 *
 *  @param enableVerbose whether to enable debug message
 *  @param testMode      whether to init in TEST mode
 */
+ (void) initWithVerboseLog:(BOOL)enableVerbose isTestMode:(BOOL)testMode;

/*!
 *  @brief check whether AD serving is enabled in backend server
 *
 *  @return BOOL
 */
+ (BOOL) isAdServing;

/*!
 *  @brief get current using crystal id
 *
 *  @return crystal id
 */
+ (NSString *) getCrystalID;

/*!
 *  @brief trigger SDK background fetch flow
 *
 *  @param success the callback block of background fetch success
 *  @param fail    the callback block of background fetch fail
 *  @param noData  the callback block of background fetch no data
 */
+ (void) triggerBackgroundFetchOnSuccess:(void (^)())success
    onFail:(void (^)())fail
    onNoData:(void (^)())noData;

/*!
 *  @brief set current active placement
 *
 *  @param placement placement string
 */
+ (void) setActivePlacement:(NSString *)placement;

/*!
 *  @brief set current active placements
 *
 *  @param placements an array of placement names
 */
+ (void) setActivePlacements:(NSArray *)placements;

#pragma mark - audience targeting
/*!
 *  @brief set audience targeting tags
 *
 *  @param tags set of tag strings
 */
+ (void) setAudienceTargetingUserTags:(NSSet<NSString *> *)tags;

#pragma mark - deep link
/*!
 *  @brief handle deeplinking
 *
 *  @param url               deeplink url
 *  @param sourceApplication sourceApplication
 */
+ (void) handleDeepLinkWithUrl:(NSURL *)url sourceApplication:(NSString *)sourceApplication;

#pragma mark - handle the open url
/*!
 * @brief handle the open url
 * 
 * @param adUrlHandler implement to handle url by app.
 */
+ (void)setAdUrlLoadingListener:(BOOL(^)(NSString *redirectUrl))adUrlHandler;

#pragma mark - check ad validity
/*!
 * @brief check if ad is still valid as time goes by
 *
 * @param ad    ad to check validity
 */
+ (BOOL)isAdValid:(Ad *)ad;

#pragma mark - block ad
/*!
 * @brief report ad blocked by user
 *
 * @param ad    ad blocked
 */
+ (void)blockAd:(Ad *)ad
      placement:(NSString *)placement
         reason:(CEAdBlockReasonCode)reason
    description:(NSString *)description;

#pragma mark - preload
/*!
 * @brief notify sdk to prepare ad for placement
 *
 * @param placement    placement to prepare ad for
 */
+ (void)preloadWithPlacement:(NSString *)placement;

#pragma mark - availability
/*!
 * @brief check if ad is available for placement
 *
 * @param placement    placement to check

 * @return BOOL
 */
+ (BOOL)isAdAvailableWithPlacement:(NSString *)placement;

#pragma mark - APP event delegate
/*!
 * @brief CrsytalExpress APP event delegate
 *
 * @param delegate to receive APP event
 */
+ (void)setAppEventDelegate:(id<I2WAPPEventDelegate>)delegate;

@end

