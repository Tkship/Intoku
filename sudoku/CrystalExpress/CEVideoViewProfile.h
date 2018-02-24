//
//  CEVideoViewProfile.h
//  crystalsdk
//
//  Copyright © 2017 intowow. All rights reserved.
//

#ifndef CEVideoViewProfile_h
#define CEVideoViewProfile_h

typedef NS_OPTIONS(NSUInteger, CEVideoViewProfile) {
    CEVideoViewProfileSpeaker             = 1 << 0,
    CEVideoViewProfileWifiTag             = 1 << 1,
    CEVideoViewProfileCountDown           = 1 << 2,
    CEVideoViewProfileAutoPlay            = 1 << 4,
    CEVideoViewProfileAutoReplay          = 1 << 5,
    CEVideoViewProfileAutoVolumeControl   = 1 << 6,
    CEVideoViewProfileSilentStart         = 1 << 7,
    CEVideoViewProfileSponsorIcon         = 1 << 8,
    CEVideoViewProfileAdIcon              = 1 << 9,
    CEVideoViewProfileSkipButton          = 1 << 10,
    CEVideoViewProfileAdCount             = 1 << 11,

    // Skip Button & Ad Count are invalid profile for CENativeAD (CEMediaView).
    CEVideoViewProfileNativeMask = CEVideoViewProfileSpeaker | CEVideoViewProfileWifiTag | CEVideoViewProfileCountDown | CEVideoViewProfileAutoPlay | CEVideoViewProfileAutoReplay| CEVideoViewProfileAutoVolumeControl | CEVideoViewProfileSilentStart | CEVideoViewProfileSponsorIcon | CEVideoViewProfileAdIcon,

    // Auto Volume Control, Skip Button & Ad Count are invalid profile for CECardAD.
    CEVideoViewProfileCardMask = CEVideoViewProfileSpeaker | CEVideoViewProfileWifiTag | CEVideoViewProfileCountDown | CEVideoViewProfileAutoPlay | CEVideoViewProfileAutoReplay| CEVideoViewProfileSilentStart | CEVideoViewProfileSponsorIcon | CEVideoViewProfileAdIcon,

    // Only Speaker, Count Down, Silent Start, Ad Icon, Skip Button & Ad Count are valid profile for CEInStreamAD.
    CEVideoViewProfileInStreamMask = CEVideoViewProfileSpeaker | CEVideoViewProfileCountDown | CEVideoViewProfileSilentStart | CEVideoViewProfileAdIcon | CEVideoViewProfileSkipButton | CEVideoViewProfileAdCount,

    CEVideoViewProfileNativeDefaultProfile   =  CEVideoViewProfileNativeMask,
    CEVideoViewProfileCardDefaultProfile     =  CEVideoViewProfileCardMask,
    CEVideoViewProfileInStreamDefaultProfile =  CEVideoViewProfileInStreamMask & (~CEVideoViewProfileSilentStart),
};

#endif /* CEVideoViewProfile_h */
