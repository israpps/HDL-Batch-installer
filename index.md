# Welcome to HDL Batch Installer website!!





<details>
  <summary> <b> Why should I use HDLBinst instead of other programs? </b> </summary>

> The idea behind this GUI consists on combining the strengths of each program that serves this same purpose.
>
> [Learn more here](./why_hdlbinst_is_better.html)

</details>

<details>
  <summary>Game Name Database </summary>

> Just like HDL Batch, this GUI will automatically search the Game Title for the PS2 ISO you're about to Install.
>
> the program has an Internal Database with `14346` Game Titles!
>
> however, you can use an external database Instead.
>
> when the program can't find the Game Title on the Database (or the Database is disabled) the name of the ISO file is assigned as the title Instead (without the extension)
>
> If you find a Game ID that isn´t registered in our database Open a new [__Database Update Request__](https://github.com/israpps/HDL-Batch-installer/issues/new?assignees=&labels=Database+issue&template=database-update-request.md&title=Database+update+Request)

  <details>
    <summary>Create Custom Database: </summary>


the sintax of the Database entry is:
```Bash
GAME_ID;GAMENAME
```
and the file must end with the line:
```
END_OF_DATABASE
```
the file should be named `gamename.DB`, and it must remain with the Program

a [copy of the internal database](https://github.com/israpps/HDL-Batch-installer/blob/main/Database/gamename.csv) is provided at this repo, (thanks to VTSTech and everyone that contributed to the game title list from PSX-Place)
  </details>
</details>
