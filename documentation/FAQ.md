---
sort: 0
---

@@ -1,105 +0,0 @@
# Frecuently Asked Questions

***

<details>
  <summary> <b> Some game installation failed, and program says `unhandled error` </b> </summary>

	**Unhandled error** Means the error does not come from the program itself, most of the time, it is an issue trown by the windows API's.
	Read the terminal logs, and you will find your error, it will be purple.
	
	If the error number is `5` or any part of the message mentions permission issues, then windows (or any installed AV) thinks HDL Batch installer is ransomware because of how it's accessing the HDD
</details>

***

<details>
  <summary> <b> Wich Program should I use to load my games after installing them? </b> </summary>

> You should use [latest stable OPL Release](https://github.com/ps2homebrew/Open-PS2-Loader/releases/latest)
  
__Note:__ There was a regression on OPL 1.1.0 regarding internal HDD, you can still give it a try... however, [OPL v1.0.0](https://github.com/ps2homebrew/Open-PS2-Loader/releases/tag/v1.0.0) is recommended for stability

</details>

***

<details>
  <summary> <b> How can I transfer cover art, themes, configs, cheats and others from my PC? </b> </summary>

 <p>

   You can use the PFSFUSE wizard that was recently implemented, you can find it on the manage HDD tab by the name "Mount Partition", this feature can mount a PFS partition as if it was a windows compatible storage device.
   
   Then you can tranfer your files to the desired partition, also, the program has a transfer Feature if you want to transfer ART and cheats downloaded by the program itself

</p>

</details>

***

<details>
  <summary> <b> I've installed a PS2 game mod (e.g: PES2020), but the program assigned the original game title (e.g: PES2014) </b> </summary>

> this program assings the game title according to the game ID, so there's no direct solution for that!
>
> the only workaround for this consists on installing the games in wich you want to use the original game title first.
>
> after installing them, load to the list all you game mods and uncheck the "Use database" checkbox under the game list

</details>

***

<details>
  <summary> <b> My game was marked as invalid game</b> </summary>

> There are a lot of things that can cause such issue:

<p>

1. Your file isn't in a supported format
2. Your file is in a supported format, but something is going on...
3. File name is too long. (Make sure that the images has less than 60 chars)

<p/>
</details>

***

<details>
  <summary> <b> How can I use a custom OSD icon for my games? </b> </summary>
    <p>
      
Take the desired custom icon and place it on the program folder (where `boot.kelf` resides) and name it as `list.ico`
      
Note: starting with `v3.1.3 - revision 0` make sure you disabled custom icon loader, otherwise, your icon will be deleted
    </p>    
  </details>

***

<details>
  <summary> <b>Could you add network support?</b> </summary>
    <p>
      
The old hdl server has been broken for years.
OPL replaced internal HDL Server with NBD Server (by @bignaux), the advantage of NBD server is that there's no need to change anything on my program to make it compatible

Just setup NBD server and the program should recognize the HDD 
      
if you don´t know how to do it, take a look at the [__OPL readme__](https://github.com/ps2homebrew/Open-PS2-Loader#introduction)
    </p>    
  </details>

***

<details>
  <summary> <b>This program is marked as malware by my antivirus</b> </summary>
    <p>
      
        Probably your Antivirus is complaining about the WNDB drivers

        You can safely use this software, there is no harm.

        If you still have doubts... simply avoid the WNBD related features
      
    </p>    
  </details>

***

## You couldn't find your question?  Try [here](https://github.com/israpps/HDL-Batch-installer/discussions) or [Here](https://github.com/israpps/HDL-Batch-installer/issues) or in our [Discord Server](https://discord.gg/wczxvrkZk6)

