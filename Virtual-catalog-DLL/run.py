import cmd,os

'''
Mit Index ist das erste Band gemeint. 
Der Bereich geht von 0-415 (die 416 einzigartigen ersten Bänder).
Siehe: http://www.afjarvis.org.uk/maths/felgenhauer_jarvis_spec1.pdf Seite 4
'''

def run():
  print("Do you want to print all ED SUdokus (y/n)")
  answer=input()

  if(answer=="y"):
    os.system("sktvcat -c0 -v0-0 -v1-415 -v2-1 > ED_Sudokus.txt") #command + Speicherort  
  else:
   print("Index of the first E.D Sudokus bands you want to print(should be between 0 and 415)")
   start=input()
   print("Index of the last  E.D Sudokus bands you want to print (should be between 0 and 415)")
   end=input()
   print("Solution will be saved in ED_Sudokus.txt")
   os.system("sktvcat -c0 -v0-{start} -v1-{end} -v2-1 > ED_Sudokus.txt ") #command + Speicherort  

if __name__=="__main__":
  run()    