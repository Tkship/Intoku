//
//  AudioPlayerHandler.h
//  sudoku
//
//  Created by Hung Kuo xin on 2018/2/27.
//  Copyright © 2018年 Hung Kuo xin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

@interface AudioPlayHandler : NSObject

@property (nonatomic, retain) AVAudioPlayer *myAudioPlayer;
+ (void) playBackgroundMusic;
+ (void) pauseBackgroundMusic;
+ (void) resumeBackgroundMusic;
@end
