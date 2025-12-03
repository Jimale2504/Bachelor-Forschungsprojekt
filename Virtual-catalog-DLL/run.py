import cmd,os

'''Wichtig! mit Index ist das erste Band gemeint, geht von 0-415 bzw. 
die 416 einzigartigen mölichkeiten das erste Band zu füllen'''

def run():
  print("Do you want to print all ED SUdokus (y/n)")
  answer=input()

  if(answer=="y"):
    os.system("sktvcat -c0 -v0-0 -v1-415 -v2-1 > D:\Sudokus\ED_Sudokus.txt") #Speicherort halt ändern
  else:
   print("Konfiguration of the first E.D Sudokus bands you want to print")
   start=input()
   print("Konfiguartion of the last  E.D Sudokus bands you want to print ")
   end=input()
   os.system("sktvcat -c0 -v0-{start} -v1-{end} -v2-1 > D:\Sudokus\ED_Sudokus.txt") #Speicherort halt ändern



if __name__=="__main__":
  run()    