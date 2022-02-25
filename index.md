# Welcome to HDL Batch Installer website!!





<details>
  <summary> <b> Why should I use HDLBinst instead of other programs? </b> </summary>
  <p>
 The idea behind this GUI consists on combining the strengths of each program that serves this same purpose.

 [Learn more here](./why_hdlbinst_is_better.html)
  </p>
</details>

----

<details>
  <summary> <b> Game Name Database </b></summary>
  <p>
  
 Just like HDL Batch, this GUI will automatically search the Game Title for the PS2 ISO you're about to Install.

 the program has an Internal Database with `15177` Game Titles!

 however, you can use an external database Instead.

 when the program can't find the Game Title on the Database (or the Database is disabled) the name of the ISO file is assigned as the title Instead (without the extension)

 If you find a Game ID that isn´t registered in our database Open a new [__Database Update Request__](https://github.com/israpps/HDL-Batch-installer/issues/new?assignees=&labels=Database+issue&template=database-update-request.md&title=Database+update+Request)
  </p>
  <details>
    <summary>Create Custom Database: </summary>
    <p>    
      
the file should be named `gamename.DB`, it must remain with the Program

a [copy of the internal database](https://github.com/israpps/HDL-Batch-installer/blob/main/Database/gamename.csv) is provided at this repo, (thanks to VTSTech and everyone that contributed to the game title list from PSX-Place)
    </p>    
  </details>
</details>

-----

<details>
  <summary> <b> Command line arguments </b></summary>
  <p>
  
`--stay-on-top`	forces the GUI to stay on top of every program.

`--redirect-text` redirects log messages from console into two text files found inside `log` folder.

`--force-max-debug` Program will behave as if highest debug level was selected, independently of the value written on the config file.

  </p>    
</details>

-----

<details>
  <summary> <b> Custom Icon Loader </b> </summary>
  <p>
    
Starting with `v3.1.3 - revision 0` HDLBinst will be capable of loading custom icons (wich will be the icon that the game uses as save file
    
#### If you want to contribute to the icon database you must:
1. Find the game icom (from the save file is the best option)
2. check if the icon file size is smaller than 200kb
3. check all the game variants ELF ID
4. send me the file and a list with the ELF ID of the game variants (search the game title on this [Database](https://github.com/israpps/HDL-Batch-installer/blob/main/Database/gamename.csv) to see how many variants are available and copy the ELF of each
    
__Example:__

GTA San andreas
    
*Provide icon file* (example name: `GTA_SAR.ico`)

and a list of the ELF ID's like this one
```ini
SCES_515.41=GTA_SAR.ico
SCES_525.41=GTA_SAR.ico
SCES_529.27=GTA_SAR.ico
SLES_515.41=GTA_SAR.ico
SLES_525.41=GTA_SAR.ico
SLPM_552.92=GTA_SAR.ico
SLES_529.27=GTA_SAR.ico
SLPM_659.84=GTA_SAR.ico
SLPM_667.88=GTA_SAR.ico
SLUS_209.46=GTA_SAR.ico
```
    
  </p>
</details>

-----
## [FAQ:](./FAQ/FAQ.html)
