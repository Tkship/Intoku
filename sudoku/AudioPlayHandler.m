//
//  AudioPlayerHandler.m
//  sudoku
//
//  Created by Hung Kuo xin on 2018/2/27.
//  Copyright © 2018年 Hung Kuo xin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AudioPlayHandler.h"

@interface AudioPlayHandler ()
@end

@implementation AudioPlayHandler

AVAudioPlayer *myAudioPlayer;

+ (void) playBackgroundMusic {
    //start a background sound
    NSString *soundFilePath = [[NSBundle mainBundle] pathForResource:@"background_music" ofType: @"mp3"];
    NSURL *fileURL = [[NSURL alloc] initFileURLWithPath:soundFilePath ];
    myAudioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:fileURL error:nil];
    myAudioPlayer.numberOfLoops = -1; //infinite loop
    [myAudioPlayer play];
}

+ (void) pauseBackgroundMusic {
    //stop a background sound
    if (myAudioPlayer != NULL) [myAudioPlayer pause];
}

+ (void) resumeBackgroundMusic {
    //stop a background sound
    if (myAudioPlayer != NULL) [myAudioPlayer play];
}

+ (void) playButtonSound {
    //stop a background sound
    if (myAudioPlayer != NULL) [myAudioPlayer pause];
}
@end
