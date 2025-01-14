"Resource/HudLayout.res"
{
	HudHealth
	{
		"fieldName"		"HudHealth"
		//	"xpos"	"16"
		"xpos"	"13.5"
	//	"ypos"	"432"
	//	"ypos"	"443"
		"ypos"	"445"
		"wide"	"102"
	//	"tall"  "36"
		"tall"  "27"
		"visible" "1"
		"enabled" "1"

		"PaintBackgroundType"	"2"
		
		"text_xpos" "0"
		"text_ypos" "1"
	//	"text_width" "29"
	//	"text_height" "9"
		"text_width" "31"
		"text_height" "8"
	//	"digit_xpos" "6"
	//	"digit_xpos" "36"
		"digit_xpos" "38"
		"digit_ypos" "9"
	//	"digit_height" "18"
		"digit_height" "17" // VXP: Good!
		
		"NumberFont"		"HudNumbers2"
		"NumberGlowFont"	"HudNumbersGlow2"
		"TextFont"			"Default2"
	}
	HudHealth [$X360]
	{
		"fieldName"		"HudHealth"
		"xpos"	"48"
		"ypos"	"416"
		"wide"	"115"
		"tall"  "36"
		"visible" "1"
		"enabled" "1"

		"PaintBackgroundType"	"2"
		
		"text_xpos" "8"
		"text_ypos" "18"
		"digit_xpos" "60"
		"digit_ypos" "-1"
	}
	
	HudSuit
	{
		"fieldName"		"HudSuit"
	//	"xpos"	"90"
	//	"xpos"	"79"
		"xpos"	"80"
	//	"ypos"	"432"
	//	"ypos"	"443"
		"ypos"	"445"
	//	"wide"	"108"
		"wide"	"102"
	//	"tall"  "36"
		"tall"  "27"
		"visible" "1"
		"enabled" "1"

		"PaintBackgroundType"	"2"

		"text_xpos" "0"
		"text_ypos" "1"
	//	"text_width" "25"
		"text_width" "24.8"
		"text_height" "8"
	//	"digit_xpos" "6"
	//	"digit_xpos" "36"
		"digit_xpos" "38"
		"digit_ypos" "9"
		"digit_height" "17"
		
		"NumberFont"		"HudNumbers2"
		"NumberGlowFont"	"HudNumbersGlow2"
		"TextFont"			"Default2"
	}
	HudSuit [$X360]
	{
		"fieldName"		"HudSuit"
		"xpos"	"176"
		"ypos"	"416"
		"wide"	"117"
		"tall"  "36"
		"visible" "1"
		"enabled" "1"

		"PaintBackgroundType"	"2"

		"text_xpos" "8"
		"text_ypos" "18"
		"digit_xpos" "50"
		"digit_ypos" "-1"
	}

	HudAmmo
	{
		"fieldName" "HudAmmo"
		"xpos"	"r20"
	//	"ypos"	"432"
	//	"ypos"	"443"
		"ypos"	"445"
	//	"wide"	"100"
		"wide"	"102"
	//	"tall"  "30"
	//	"tall"  "36"
		"tall"  "27"
		"visible" "1"
		"enabled" "1"

		"PaintBackgroundType"	"2"
	//	"Color" "177 150 70 255"
	//	"Color" "247 192 84 255"
	//	"Color" "OldFgColor"

		"text_xpos" "0"
		"text_ypos" "1"
	//	"text_width" "27"
	//	"text_width" "24"
		"text_width" "25"
	//	"text_height" "9"
		"text_height" "8"
	//	"digit_xpos" "6"
	//	"digit_xpos" "50"
	//	"digit_xpos" "36"
		"digit_xpos" "38"
		"digit_ypos" "9"
	//	"digit_height" "18"
		"digit_height" "17"
	//	"digit2_xpos" "70"
	//	"digit2_xpos" "75"
	//	"digit2_xpos" "80" // digit_xpos + 30
	//	"digit2_xpos" "66"
	//	"digit2_xpos" "63"
	//	"digit2_xpos" "62"
	//	"digit2_xpos" "66"
		"digit2_xpos" "64"
	//	"digit2_ypos" "4"
		"digit2_ypos" "13"
		"digit2_height" "9"
		
		"NumberFont"		"HudNumbers2"
		"NumberGlowFont"	"HudNumbersGlow2"
		"TextFont"			"Default2"
	}
	HudAmmo	[$X360]
	{
		"fieldName" "HudAmmo"
		"xpos"	"r208"
		"ypos"	"416"
		"wide"	"160"
		"tall"  "36"
		"visible" "1"
		"enabled" "1"

		"PaintBackgroundType"	"2"

		"text_xpos" "8"
		"text_ypos" "18"
		"digit_xpos" "60"
		"digit_ypos" "-1"
		"digit2_xpos" "120"
		"digit2_ypos" "14"
	}

	HudAmmoSecondary
	{
	//	"xpos"	"r53"
		"xpos"	"r27"
	//	"ypos"	"432"
	//	"ypos"	"443"
	//	"ypos"	"445"
		"ypos"	"454"
	//	"wide"	"60"
	//	"wide"	"80"
		"wide"	"17"
	//	"tall"  "30"
	//	"tall"  "27"
		"tall"  "16"
		"visible" "1"
		"enabled" "1"

		"PaintBackgroundType"	"0"
	//	"Color" "177 150 70 255"
	//	"Color" "OldFgColor"

	//	"digit_xpos" "10"
	//	"digit_xpos" "50"
	//	"digit_xpos" "35"
	//	"digit_ypos" "13"

		// VXP: WTF? Why this offset?
		"digit_xpos" "15"
		"digit_ypos" "4"

	//	"digit_xpos" "1"
	//	"digit_ypos" "1"
		"digit_height" "9"
		
		"NumberFont"		"HudNumbers2"
		"NumberGlowFont"	"HudNumbersGlow2"
		"TextFont"			"Default2"
	}
	HudAmmoSecondary	[$X360]
	{
		"fieldName" "HudAmmoSecondary"
		"xpos"	"r113"
		"ypos"	"416"
		"wide"	"65"
		"tall"  "36"
		"visible" "1"
		"enabled" "1"

		"PaintBackgroundType"	"2"

		"text_xpos" "8"
		"text_ypos" "22"
		"digit_xpos" "36"
		"digit_ypos" "-1"
	}
	
	HudSuitPower
	{
		"visible" "1"
		"enabled" "1"
	//	"xpos"	"16"
	//	"xpos"	"187" // 79 + 108 (HudSuit2's xpos + wide)
		"xpos"	"145"
	//	"ypos"	"396"
		"ypos"	"454" // 445 + 9 (HudSuit2's ypos + text_height)
	//	"wide"	"102"
	//	"tall"	"30"
	//	"wide"	"80"
		"wide"	"70"
		"tall"	"12"
		
		"AuxPowerLowColor" "255 0 0 220"
	//	"AuxPowerHighColor" "255 220 0 220"
		"AuxPowerHighColor" "177 150 70 255"
	//	"AuxPowerDisabledAlpha" "70"
		"AuxPowerDisabledAlpha" "255"

	//	"Color" "177 150 70 255" // No use of this

	//	"BarInsetX" "8"
	//	"BarInsetY" "8"
	//	"BarWidth" "92"
	//	"BarHeight" "4"
		"BarInsetX" "0"
		"BarInsetY" "0"
		"BarWidth" "70" // Same as wide
		"BarHeight" "12" // Same as tall

		"PaintBackgroundType"	"2"
	}
	HudSuitPower	[$X360]
	{
		"fieldName" "HudSuitPower"
		"visible" "1"
		"enabled" "1"
		"xpos"	"48"
		"ypos"	"370"
		"wide"	"102"
		"tall"	"26"
		
		"AuxPowerLowColor" "255 100 0 220"
		"AuxPowerHighColor" "255 220 0 220"
		"AuxPowerDisabledAlpha" "70"

		"BarInsetX" "8"
		"BarInsetY" "19"
		"BarWidth" "92"
		"BarHeight" "5"
		"BarChunkWidth" "6"
		"BarChunkGap" "3"

		"text_xpos" "8"
		"text_ypos" "4"
		"text2_xpos" "8"
		"text2_ypos" "25"
		"text2_gap" "12"

		"PaintBackgroundType"	"2"
	}

	HudPosture	[$WIN32]
	{
		"fieldName" 		"HudPosture"
		"visible" 		"1"
		"PaintBackgroundType"	"2"
		"xpos"	"16"
		"ypos"	"316"
		"tall"  "36"
		"wide"	"36"
		"font"	"WeaponIconsSmall"
		"icon_xpos"	"10"
		"icon_ypos" 	"0"
	}
	HudPosture	[$X360]
	{
		"fieldName" 		"HudPosture"
		"visible" 		"1"
		"PaintBackgroundType"	"2"
		"xpos"	"48"
		"ypos"	"316"
		"tall"  "36"
		"wide"	"36"
		"font"	"WeaponIconsSmall"
		"icon_xpos"	"10"
		"icon_ypos" 	"2"
	}
	
	HudFlashlight
	{
		"fieldName" "HudFlashlight"
		"visible" "0"
		"PaintBackgroundType"	"2"
		"xpos"	"16"		[$WIN32]
		"ypos"	"370"		[$WIN32]
		"xpos_hidef"	"293"		[$X360]		// aligned to left
		"xpos_lodef"	"c-18"		[$X360]		// centered in screen
		"ypos"	"428"		[$X360]				
		"tall"  "20"
		"wide"	"102"
		"font"	"WeaponIconsSmall"
		
		"icon_xpos"	"4"
		"icon_ypos" "-8"
		
		"BarInsetX" "4"
		"BarInsetY" "18"
		"BarWidth" "28"
		"BarHeight" "2"
		"BarChunkWidth" "2"
		"BarChunkGap" "1"
	}
	HudDamageIndicator
	{
		"fieldName" "HudDamageIndicator"
		"visible" "1"
		"enabled" "1"
		"DmgColorLeft" "255 0 0 0"
		"DmgColorRight" "255 0 0 0"
		
		"dmg_xpos" "30"
		"dmg_ypos" "100"
		"dmg_wide" "36"
		"dmg_tall1" "240"
		"dmg_tall2" "200"
	}

	HudZoom
	{
		"fieldName" "HudZoom"
		"visible" "1"
		"enabled" "1"
		"Circle1Radius" "66"
		"Circle2Radius"	"74"
		"DashGap"	"16"
		"DashHeight" "4"	[$WIN32]
		"DashHeight" "6"	[$X360]		
		"BorderThickness" "88"
	}
	HudWeaponSelection
	{
		"fieldName" "HudWeaponSelection"
		"ypos" 	"16"	[$WIN32]
		"ypos" 	"32"	[$X360]
		"visible" "1"
		"enabled" "1"
		"SmallBoxSize" "32"
		"MediumBoxWide"	"95"
		"MediumBoxWide_hidef"	"78"
		"MediumBoxTall"	"50"
		"MediumBoxTall_hidef"	"50"
		"MediumBoxWide_lodef"	"74"
		"MediumBoxTall_lodef"	"50"
		"LargeBoxWide" "112"
		"LargeBoxTall" "80"
		"BoxGap" "8"
		"SelectionNumberXPos" "4"
		"SelectionNumberYPos" "4"
		"SelectionGrowTime"	"0.4"
		"TextYPos" "64"
	}

	HudCrosshair
	{
		"fieldName" "HudCrosshair"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"
		"tall"	 "480"
	}

	HudDeathNotice
	{
		"fieldName" "HudDeathNotice"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"
		"tall"	 "480"
	}

	HudVehicle
	{
		"fieldName" "HudVehicle"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"
		"tall"	 "480"
	}

	ScorePanel
	{
		"fieldName" "ScorePanel"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"
		"tall"	 "480"
	}

	HudTrain
	{
		"fieldName" "HudTrain"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"
		"tall"	 "480"
	}

	HudMOTD
	{
		"fieldName" "HudMOTD"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"
		"tall"	 "480"
	}

	HudMessage
	{
		"fieldName" "HudMessage"
		"visible" "1"
		"enabled" "1"
		"wide"	 "f0"
		"tall"	 "480"
	}

	HudMenu
	{
		"fieldName" "HudMenu"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"
		"tall"	 "480"
	}

	HudCloseCaption
	{
		"fieldName" "HudCloseCaption"
		"visible"	"1"
		"enabled"	"1"
		"xpos"		"c-250"
		"ypos"		"276"	[$WIN32]
		"ypos"		"236"	[$X360]
		"wide"		"500"
		"tall"		"136"	[$WIN32]
		"tall"		"176"	[$X360]

		"BgAlpha"	"128"

		"GrowTime"		"0.25"
		"ItemHiddenTime"	"0.2"  // Nearly same as grow time so that the item doesn't start to show until growth is finished
		"ItemFadeInTime"	"0.15"	// Once ItemHiddenTime is finished, takes this much longer to fade in
		"ItemFadeOutTime"	"0.3"
		"topoffset"		"0"		[$WIN32]
		"topoffset"		"0"	[$X360]
	}

	HudChat
	{
		"fieldName" "HudChat"
		"visible" "0"
		"enabled" "1"
		"xpos"	"0"
		"ypos"	"0"
		"wide"	 "4"
		"tall"	 "4"
	}

	HudHistoryResource	[$WIN32]
	{
		"fieldName" "HudHistoryResource"
		"visible" "1"
		"enabled" "1"
		"xpos"	"r252"
		"ypos"	"40"
		"wide"	 "248"
		"tall"	 "320"

		"history_gap"	"56" [!$OSX]
		"history_gap"	"64" [$OSX]
		"icon_inset"	"38"
		"text_inset"	"36"
		"text_inset"	"26"
		"NumberFont"	"HudNumbersSmall"
	}
	HudHistoryResource	[$X360]
	{
		"fieldName" "HudHistoryResource"
		"visible" "1"
		"enabled" "1"
		"xpos"	"r300"
		"ypos"	"40" 
		"wide"	 "248"
		"tall"	 "240"

		"history_gap"	"50"
		"icon_inset"	"38"
		"text_inset"	"36"
		"NumberFont"	"HudNumbersSmall"
	}

	HudGeiger
	{
		"fieldName" "HudGeiger"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"
		"tall"	 "480"
	}

	HUDQuickInfo
	{
		"fieldName" "HUDQuickInfo"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"
		"tall"	 "480"
	}

	HudWeapon
	{
		"fieldName" "HudWeapon"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"
		"tall"	 "480"
	}
	HudAnimationInfo
	{
		"fieldName" "HudAnimationInfo"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"
		"tall"	 "480"
	}

	HudPredictionDump
	{
		"fieldName" "HudPredictionDump"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"
		"tall"	 "480"
	}

	HudHintDisplay
	{
		"fieldName"				"HudHintDisplay"
		"visible"				"0"
		"enabled"				"1"
		"xpos"					"c-240"
		"ypos"					"c60"
		"xpos"	"r148"	[$X360]
		"ypos"	"r338"	[$X360]
		"wide"					"480"
		"tall"					"100"
		"HintSize"				"1"
		"text_xpos"				"8"
		"text_ypos"				"8"
		"center_x"				"0"	// center text horizontally
		"center_y"				"-1"	// align text on the bottom
		"paintbackground"		"0"
	}	

	HudHintKeyDisplay
	{
		"fieldName"	"HudHintKeyDisplay"
		"visible"	"0"
		"enabled" 	"1"
		"xpos"		"r120"	[$WIN32]
		"ypos"		"r340"	[$WIN32]
		"xpos"		"r148"	[$X360]
		"ypos"		"r338"	[$X360]
		"wide"		"100"
		"tall"		"200"
		"text_xpos"	"8"
		"text_ypos"	"8"
		"text_xgap"	"8"
		"text_ygap"	"8"
		"TextColor"	"255 170 0 220"

		"PaintBackgroundType"	"2"
	}


	HudSquadStatus	[$WIN32]
	{
		"fieldName"	"HudSquadStatus"
		"visible"	"1"
		"enabled" "1"
		"xpos"	"r120"
		"ypos"	"380"
		"wide"	"104"
		"tall"	"46"
		"text_xpos"	"8"
		"text_ypos"	"34"
		"SquadIconColor"	"255 220 0 160"
		"IconInsetX"	"8"
		"IconInsetY"	"0"
		"IconGap"		"24"

		"PaintBackgroundType"	"2"
	}
	HudSquadStatus	[$X360]
	{
		"fieldName"	"HudSquadStatus"
		"visible"	"1"
		"enabled" "1"
		"xpos"	"r182"
		"ypos"	"348"
		"wide"	"134"
		"tall"	"62"
		"text_xpos"	"8"
		"text_ypos"	"44"
		"SquadIconColor"	"255 220 0 160"
		"IconInsetX"	"8"
		"IconInsetY"	"-4"
		"IconGap"		"24"
		"IconFont"		"SquadIcon"

		"PaintBackgroundType"	"2"
	}

	HudPoisonDamageIndicator	[$WIN32]
	{
		"fieldName"	"HudPoisonDamageIndicator"
		"visible"	"0"
		"enabled" "1"
		"xpos"	"16"
		"ypos"	"346"
		"wide"	"136"
		"tall"	"38"
		"text_xpos"	"8"
		"text_ypos"	"8"
		"text_ygap" "14"
		"TextColor"	"255 170 0 220"
		"PaintBackgroundType"	"2"
	}
	HudPoisonDamageIndicator	[$X360]
	{
		"fieldName"	"HudPoisonDamageIndicator"
		"visible"	"0"
		"enabled" "1"
		"xpos"	"48"
		"ypos"	"264"
		"wide"	"192"
		"tall"	"46"
		"text_xpos"	"8"
		"text_ypos"	"6"
		"text_ygap" "16"
		"TextColor"	"255 170 0 220"
		"PaintBackgroundType"	"2"
	}

	HudCredits
	{
		"fieldName"	"HudCredits"
		"TextFont"	"Default"
		"visible"	"1"
		"xpos"	"0"
		"ypos"	"0"
		"wide"	"640"
		"tall"	"480"
		"TextColor"	"255 255 255 192"

	}
	
	HUDAutoAim
	{
		"fieldName" "HUDAutoAim"
		"visible" "1"
		"enabled" "1"
		"wide"	 "640"	[$WIN32]
		"tall"	 "480"	[$WIN32]
		"wide"	 "960"	[$X360]
		"tall"	 "720"	[$X360]
	}

	HudCommentary
	{
		"fieldName" "HudCommentary"
		"xpos"	"c-190"
		"ypos"	"350"
		"wide"	"380"
		"tall"  "40"
		"visible" "1"
		"enabled" "1"
		
		"PaintBackgroundType"	"2"
		
		"bar_xpos"		"50"
		"bar_ypos"		"20"
		"bar_height"	"8"
		"bar_width"		"320"
		"speaker_xpos"	"50"
		"speaker_ypos"	"8"
		"count_xpos_from_right"	"10"	// Counts from the right side
		"count_ypos"	"8"
		
		"icon_texture"	"vgui/hud/icon_commentary"
		"icon_xpos"		"0"
		"icon_ypos"		"0"		
		"icon_width"	"40"
		"icon_height"	"40"
	}
	
	HudHDRDemo
	{
		"fieldName" "HudHDRDemo"
		"xpos"	"0"
		"ypos"	"0"
		"wide"	"640"
		"tall"  "480"
		"visible" "1"
		"enabled" "1"
		
		"Alpha"	"255"
		"PaintBackgroundType"	"2"
		
		"BorderColor"	"0 0 0 255"
		"BorderLeft"	"16"
		"BorderRight"	"16"
		"BorderTop"		"16"
		"BorderBottom"	"64"
		"BorderCenter"	"0"
		
		"TextColor"		"255 255 255 255"
		"LeftTitleY"	"422"
		"RightTitleY"	"422"
	}

	AchievementNotificationPanel	
	{
		"fieldName"				"AchievementNotificationPanel"
		"visible"				"1"
		"enabled"				"1"
		"xpos"					"0"
		"ypos"					"180"
		"wide"					"f10"	[$WIN32]
		"wide"					"f60"	[$X360]
		"tall"					"100"
	}

	CHudVote
	{
		"fieldName"		"CHudVote"
		"xpos"			"0"			
		"ypos"			"0"
		"wide"			"640"
		"tall"			"480"
		"visible"		"1"
		"enabled"		"1"
		"bgcolor_override"	"0 0 0 0"
		"PaintBackgroundType"	"0" // rounded corners
	}	
	
	//LeakNet
	CHudAR2Mode
	{
		"fieldName"		"CHudAR2Mode"
		"visible"		"1"
		"enabled"		"1"
		"xpos"			"r100"
		"ypos"			"400"
		"wide"			"40"
		"tall"			"25"

		"icon_xpos"		"0"
		"icon_ypos"		"0"
	}
}