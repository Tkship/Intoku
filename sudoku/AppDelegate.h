//
//  AppDelegate.h
//  sudoku
//
//  Created by Jose Rojas on 12/21/14.
//  Copyright (c) 2014 Jose Rojas. All rights reserved.
//


#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate> {
    AVAudioPlayer *myAudioPlayer;
}

@property (strong, nonatomic) UIWindow *window;
@property (nonatomic, retain) AVAudioPlayer *myAudioPlayer;

@end
