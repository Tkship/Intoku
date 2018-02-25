//
//  DemoNewGameViewController.m
//  sudoku
//
//  Created by Hung Kuo xin on 2018/2/22.
//  Copyright © 2018年 Hung Kuo xin. All rights reserved.
//

#import "DemoNewGameViewController.h"
#import "CESplash2AD.h"

@interface DemoNewGameViewController ()

@end
@interface DemoNewGameViewController() <CESplash2ADDelegate>{
    CESplash2AD *ceSplash2AD;
}
@end

@implementation DemoNewGameViewController

-(void) viewDidLoad {
    [super viewDidLoad];
    self.NewGamebtn.layer.cornerRadius = 12;
    self.NewGamebtn.layer.shadowOffset = CGSizeMake(0, 2);
    self.NewGamebtn.layer.shadowColor = UIColor.blackColor.CGColor;
    self.NewGamebtn.layer.masksToBounds = NO;
    self.NewGamebtn.layer.shadowOpacity = 28/255;
    
}
- (IBAction)buttonTouchUp:(id)sender {
    [self splashADDidRequest];
    //[self dismissViewControllerAnimated:YES completion:nil];
}
//- (void) _setViewDelegateContentOverlayInsetsAreClean: (id)sender {}

/*!
 *
 * @brief send splash viedo request to load ads, and it will display ads while loading successfully.
 *
 */
-(void) splashADDidRequest
{
    ceSplash2AD = [[CESplash2AD alloc] initWithPlacement:@"END_INTERSTITUAL"];
    ceSplash2AD.delegate = self;
    [ceSplash2AD loadAd];
}

#pragma mark - CESplash2ADDelegate
- (void)splash2ADDidLoaded:(CESplash2AD*)splash2AD
{
    UIViewController *topController = [UIApplication sharedApplication].keyWindow.rootViewController;
    while (topController.presentedViewController) {
        topController = topController.presentedViewController;
    }
    
    [ceSplash2AD showFromViewController:topController animated:YES];
}

- (void) splash2ADDidVideoStart:(nonnull CESplash2AD *)splash2AD
{
    
    [self appendLog:@"splash2ADDidVideoStart"];
}

- (void) splash2ADWillDismiss:(nonnull CESplash2AD *)splash2AD
{
    
    [self appendLog:@"splash2ADWillDismiss"];
}

- (void) splash2ADDidDismiss:(nonnull CESplash2AD *)splash2AD
{
    [self appendLog:@"splash2ADDidDismiss"];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)appendLog:(NSString *)log {
    NSString* format = @"HH:mm:ss.SSS";
    
    // Set up an NSDateFormatter for UTC time zone
    NSDateFormatter* dateFtr = [[NSDateFormatter alloc] init];
    [dateFtr setDateFormat:format];
    [dateFtr setTimeZone:[NSTimeZone localTimeZone]];
    
    NSLog(@"%@", log);
    self.logTextView.text = [NSString stringWithFormat:@"%@  %@\n%@", [dateFtr stringFromDate:[NSDate date]], log, self.logTextView.text];
}

@end


