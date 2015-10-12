F15::
	Loop, 50
	{
		SoundSet -2
		Sleep, 35
	}
	Send, {Media_Play_Pause}
	Sleep, 15000
	Send, {Media_Play_Pause}
	Loop, 50
	{
		SoundSet +2
		Sleep, 60
	}