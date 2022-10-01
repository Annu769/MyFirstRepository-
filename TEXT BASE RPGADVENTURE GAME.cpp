#include <bits/stdc++.h>
#include <unistd.h>
#define CLRSCR "\e[2J\e[H";
#define RED "\x1b[31m";
#define GREEN "\x1b[32m";
#define BLUE "\x1b[34m";
#define MAGENTA "\x1b[35m";
#define WHITE "\x1b[37m";
using namespace std;


string Name;

int intro, p_MaxHealth = 200;

bool Map = false, sword = false, shield = false, armour = false, bow = false;

int enemy1 = 0, enemy2 = 0, enemy3 = 0, enemy4 = 0, enemy5 = 0,boss1 = 0, player1 = 0;

bool C_hit = false, block = false, Steallife = false, ranDmg = false;

void SlectLevel();
void battleLoop(int,int);


//INTERFACE CLASS
class CharControl
{
public:
int P_health;
int  m_damage;
void setPlayerHealth(int hp)
{
  P_health = hp;
}
int GetP_Health()
{
  return P_health;
}
virtual void TakeDamage(int) = 0;
virtual int addDamage() = 0;
};
//PLAYER CLASS
class Kratos : public CharControl{
  private:
int Ad_Damage;
public:
Kratos()
{
  if(armour == 1)
    setPlayerHealth(p_MaxHealth + 50);
  
else
    setPlayerHealth(p_MaxHealth);
  
}
int addDamage()
{  srand(time(NULL));
  int m_Damage = rand() %(20-17+1)+ 15;
  int hit = rand()% 6 + 1;
  if( C_hit && hit > 2){
    m_Damage += 10;
    cout<<GREEN;
    cout<<Name<<"'s Give A critical Hit "<<m_Damage<<"\n";
    
    
  }
  return m_Damage;
}

void TakeDamage(int _rdh)
{ P_health -= _rdh;
  if(P_health <= 0)
  {
    P_health = 0;
  }
  setPlayerHealth(P_health);
}

void LifeStealHealing(int hp)
{
  P_health += hp;
  cout<<GREEN;
  cout<<Name<<" Used Steal Ability To  Recover Our health by "<<hp<<" Points\n";
  if(P_health >= 200){
    P_health = 200;
  }
   cout<<Name<<"'s Health: "<<P_health<<endl<<endl<<RED;
}
int PlayerHealing()
{
  srand(time(NULL));
  int plus_hp = rand() % (25 - 6 +1)+14;
 
  if(P_health < 200)
  {
    P_health += plus_hp;
    cout<<GREEN;
    cout<<"Player  use 'BABA JI KI BUTTI' healing Your self by "<<plus_hp<<"\n";
    if(P_health >=200)
    {
      P_health = 200;
    }
    else if(P_health == 200) {
      cout<<Name<<"'s Health already full can not heal yourself\n";
    }
  }
  return plus_hp;
}

};

//ENEMY CLASS
class Enemy: public CharControl
{
  public:
  Enemy()
  {
  setPlayerHealth(80);
  }
  int addDamage()
  {
  srand(time(NULL));
  int Admg = rand()% (17-5+1)+6;
  return Admg;
  
  }
  void TakeDamage(int d)
  {
   P_health -= d;
  if(P_health <= 0)
  {
    P_health = 0;
  }
  setPlayerHealth(P_health);
  }
  int DifenseOrAtack()
  {srand(time(NULL));
  return rand() % 4+1;
  }
};


//BOSS CLASS
class Boss:public CharControl{
public:
Boss()
{
  setPlayerHealth(250);
}

int addDamage()
{
  srand(time(NULL));
  int Admg = rand () % (20 - 10 + 1 )+10;
  return Admg;
}

void TakeDamage(int hp)
{
  P_health -= hp;
if(P_health <= 0)
{
  P_health = 0;
}
  setPlayerHealth(P_health);
}

void HealRegeneration(int heal)
{
  P_health += heal;
  cout<<GREEN;
  cout<<"Murloc Recover His Health By "<<heal<<endl<<GREEN
    if(P_health >= 250)
  {
    P_health = 250;
  }
}

int GroundSlash()
{
  srand(time(NULL));
   cout<<RED;
    cout<<"Murlocs used his Ground Slash Ability! "<<endl<<endl<<GREEN;
  int meleeDmg = rand() % (20 - 10 + 1) + 20; 
    return meleeDmg;
}

int DifenseOrGroundSlash()
{srand(time(NULL));
  return rand() % 6+1;
}

};

void Print()
{
  
  cout<<"||===========================================================================================================||\n\n";
  sleep(1);

}

// LEVEL COMPLETE
void levelCompleted(int numlv)
{
  cout<<"\t\t============== Level "<<numlv<<" Completed ================\n";
  sleep(3);
  cout<<CLRSCR;
}

// LOCKED LEVEL
void Lockedlv()
{
  cout<<"\n\n\t ====== Complete Previos Level to unlock this level! ========"<<"\t\t\t\t\t\n  Please Wait.....\n\n";
  sleep(3);
  cout<<CLRSCR;
  SlectLevel();
}

// UNLOCKED LEVEL
void Unlockedlv(int Level){
  if(Level == 5)
  
    cout<<"============== BOSS LEVEL UNLOCKED ==================\n";
  else
    cout<<"============== LEVEL "<<Level + 1<<" UNLOCKED =================\n";
  cout<<WHITE;
  sleep(3);
  cout<<CLRSCR;
 
}


void gameEnd()
{
  cout<<CLRSCR;
  cout<<"\t\t\t======================= GAME OVER!!!!! ======================\n";
  cout<<"\t\t\t================ YOU FAILED TO DEFEAT MURLOC ================\n";
}

// ENEMY SLECTION
int EnemySlection(int levelNumber)
{
  cout<<RED;
  int choice;
   switch(levelNumber){
    case 1:
      while(enemy1 == 0){
        if(player1 == 0){
          cout<<"Select which Enemy you want to Attack "<<endl<<endl;
          cout<<"1. Enemy 1"<<endl<<endl;
          cin>>choice;
          if(choice != 1){cout<<"Please select a valid option! "<<endl<<endl;}
            
          else{ battleLoop(choice,levelNumber);}
           
        }      
      }
      if(enemy1 == 1){
        enemy1 = 0;
        levelCompleted(levelNumber);
        SlectLevel();
      }
      else if( player1 == 1){
        gameEnd();
      }
      break;
    
    
    case 2:
      while(enemy1 == 0 || enemy2 == 0){
        if(player1 == 0){
          cout<<"Select which Enemy you want to Attack "<<endl<<endl;
          cout<<"1. Enemy 1"<<endl;
          cout<<"2. Enemy 2"<<endl<<endl;
          cin>>choice;  
          if((choice == 1 && enemy1 == 1) || (choice == 2 && enemy2 == 1))
          { 
            cout<<"This Enemy is already Defeated! "<<endl;
            }
            
          else if(choice == 1 || choice == 2)
          {
            battleLoop(choice,levelNumber);
            }
            
          else{
            cout<<"Please select a valid option! "<<endl<<endl;
            }
            
        }
      }
      if(enemy1 == 1 && enemy2 == 1){
        enemy1 = enemy2 = 0;
        levelCompleted(levelNumber);
        SlectLevel();
      }
      else if( player1 == 1){
        gameEnd();
      }
      break;
    
    case 3:
      while(enemy1 == 0 || enemy2 == 0 || enemy3 == 0){
        if(player1 == 0){
          cout<<"Select which Enemy you want to Attack "<<endl<<endl;
          cout<<"1. Enemy 1"<<endl;
          cout<<"2. Enemy 2"<<endl;
          cout<<"3. Enemy 3"<<endl<<endl;
          cin>>choice;  
          if((choice == 1 && enemy1 == 1) || (choice == 2 && enemy2 == 1)|| (choice == 3 && enemy3 == 1))
          {cout<<"This Enemy is already Defeated! "<<endl;}
            
          else if(choice == 1 || choice == 2 || choice == 3){
            battleLoop(choice,levelNumber);
            }
            
          else {
              cout<<"Please select a valid option! "<<endl<<endl;
          }
          
        }
      }
      if(enemy1 == 1 && enemy2 == 1 && enemy3 == 1){
        enemy1 = enemy2 = enemy3 = 0;
        levelCompleted(levelNumber);
        SlectLevel();
      }
      else if( player1 == 1){
        gameEnd();
      }
      break;
    
     case 4:
       
          while(enemy1 == 0 || enemy2 == 0 || enemy3 == 0 || enemy4 == 0)
            {
               if(player1 == 0){                   
          cout<<"Select which Enemy you want to Attack "<<endl<<endl;
          cout<<"1. Enemy 1"<<endl;
          cout<<"2. Enemy 2"<<endl;
          cout<<"3. Enemy 3"<<endl;
          cout<<"4. Enemy 4"<<endl<<endl;
          cin>>choice;  
          if((choice == 1 && enemy1 == 1) || (choice == 2 && enemy2 == 1)|| (choice == 3 && enemy3 == 1) || (choice == 4 && enemy4 == 1))
            {cout<<"This Enemy is already Defeated! "<<endl;}
           
          else if(choice == 1 || choice == 2 || choice == 3 || choice == 4){
            battleLoop(choice,levelNumber);}
          else {
            cout<<"Please select a valid option! "<<endl<<endl;}
        }
            }
           if(enemy1 == 1 && enemy2 == 1 && enemy3 == 1 && enemy4 == 1){
        enemy1 = enemy2 = enemy3 = enemy4 = 0;                                                
        levelCompleted(levelNumber);
        SlectLevel();
      }
      else if( player1 == 1){
        gameEnd();
      }
         
         break;
       
     case 5:
       
          while(enemy1 == 0 || enemy2 == 0 || enemy3 == 0 || enemy4 == 0 || enemy5 == 0)
            {
              if(player1 == 0){
          cout<<"Select which Enemy you want to Attack "<<endl<<endl;
          cout<<"1. Enemy 1"<<endl;
          cout<<"2. Enemy 2"<<endl;
          cout<<"3. Enemy 3"<<endl;
          cout<<"4. Enemy 4"<<endl;
          cout<<"5. Enemy 5"<<endl<<endl;
          cin>>choice;  
          if((choice == 1 && enemy1 == 1) || (choice == 2 && enemy2 == 1)|| (choice == 3 && enemy3 == 1) || (choice == 4 && enemy4 == 1)||(choice == 5 && enemy5 ==1))
            {cout<<"This Enemy is already Defeated! "<<endl;}
          else if(choice == 1 || choice == 2 || choice == 3 || choice == 4||choice == 5){
            battleLoop(choice,levelNumber);}
          else {
            cout<<"Please select a valid option! "<<endl<<endl;}
              }
            }
           if(enemy1 == 1 && enemy2 == 1 && enemy3 == 1 && enemy4 == 1 && enemy5 == 1){
        enemy1 = enemy2 = enemy3 = enemy4 = enemy5 = 0;                                                
        levelCompleted(levelNumber);
        SlectLevel();
      }
      else if( player1== 1){
        gameEnd();
      }
         break;
       
    case 6:
      while(boss1 == 0)
      {
        if(player1 == 0){
          int choice;
          cout<<"Press '1' To Fight  MURLOCS (BOSS)! "<<endl<<endl;
          cin>>choice;
          if(choice == 1)
          {
             battleLoop(choice,levelNumber);
            
            }
          else{
            cout<<"Please select a valid option! "<<endl<<endl;
            }
        }
      }
      if(boss1 == 1){
         boss1 = 0;
        levelCompleted(levelNumber);
        cout<<"******************** GAME COMPLETED! ******************** "<<endl<<endl;
        cout<<"****************** YOU DEFEATED MURLOC ****************** "<<endl;
      }
      else if( player1 == 1){
        gameEnd();
      }
      break;
    default:
      cout<<"Level Doesn't Exist!! "<<endl;
  }
  return choice;
}
//BOSS TAKING DAMAGE FUCTION
int PlayerAttacktoboss(int healGrslash,int *murlocSplAttack,int plyerattack,int plyerRange,bool bossTurn,Kratos &kratos,Boss &boss)
{
  cout<<GREEN;
  int AttackBoss;
  while(boss.GetP_Health() >= 0 && !bossTurn)
    {
      if(boss.DifenseOrGroundSlash() == 6 && (plyerattack == 1 || plyerRange == 1))
      {
        cout<<Name<<" Trying Attack to The boss\n";
        cout<<"====================================================================================================================\n";
        int h = rand()%(15 - 10 + 1)+6;
        boss.TakeDamage(0);
        cout<<"OH NO! MURLOC Blocked Your Attack and use his special ability of Health Regenration!\n";
        boss.HealRegeneration(h);
        cout<<"MURLOC's Health: "<<boss.GetP_Health()<<"\n";
        sleep(3);
      }
      else if(boss.DifenseOrGroundSlash() == 4 && (plyerattack == 1 || plyerRange == 1))
      {
        cout<<Name<<" Trying Attack to The boss\n";
        cout<<"====================================================================================================================\n";
        int dmg = kratos.addDamage();
        boss.TakeDamage(dmg);
        cout<<"MURLOC's Fail to block attack \n"<<GREEN;
        cout<<Name<<"'s Deal a damage of "<<dmg<<" to MURLOC! \n"<<RED;
        cout<<"MURLOC's Health Is: "<<boss.GetP_Health()<<"\n";
        *murlocSplAttack = 1;
        sleep(3);
      }
      else if(boss.DifenseOrGroundSlash() <= 3)
      {
        if(plyerattack == 1 && Steallife)
        {
          cout<<Name<<" Trying Attack to The boss\n";
          cout<<"====================================================================================================================\n";
          int dmg = kratos.addDamage();
          boss.TakeDamage(dmg);
          cout<<"MURLOC Fail To Block Attack \n"<<GREEN;
          cout<<Name<<"'s Deals A Damage Of: "<<dmg<<" To MURLOC! \n"<<RED;
          cout<<"MURLOC's Health: "<<boss.GetP_Health()<<"\n\n";
        kratos.LifeStealHealing(dmg - 10);
          sleep(3);
        }
        if(plyerRange == 1 && ranDmg)
        {
          cout<<Name<<" Trying Attack to The boss\n";
          cout<<"====================================================================================================================\n";
          int dmg = kratos.addDamage();
          boss.TakeDamage(dmg);
          cout<<"MURLOC Fail to Block Ranged Attack \n"<<GREEN;
          cout<<Name<<"'s Deals A Damage Of "<<dmg<<" To MURLOC! \n"<<RED;
          cout<<"MURLOC's Health: "<<boss.GetP_Health()<<"\n\n";
          sleep(3);
        }
         AttackBoss = 1;
      }
      else
      {
         AttackBoss = 1;
      }
      bossTurn = true;
    }
  if(boss.GetP_Health() <= 0)
  {
    cout<<MAGENTA;
    levelCompleted(6);
    cout<<Name<<"Cut The Murloc Head \n\n";
    cout<<"Murloc is died His soul floating in the air \n\n";
    sleep(5);
  }
  cout<<WHITE;
  return AttackBoss;
}

//EACH ENEMY TAKING DAMAGE FUCTION
int PlayerAttacktoEnemy(int atorblock, int plyerattack, int plyerRange, int enemyNum, bool enemyTurn, Kratos &kratos,Enemy &enemy)
{
  cout<<GREEN;
  int enemyAttack;
  while(enemy.GetP_Health() > 0 && !enemyTurn)
    {
      if(enemy.DifenseOrAtack() == 4 &&(plyerattack == 1 || plyerRange == 1))
      {
        cout<<Name<<" Trying Attack to The Enemy"<<enemyNum<<"\n";
        cout<<"====================================================================================================================\n";
        enemy.TakeDamage(0);        
        cout<<"OH NO This Enemy  "<<enemyNum<<" Block Your Attack \n";
        cout<<"Enemy "<<enemyNum<<"'s Health is: "<<enemy.GetP_Health()<<"\n\n";
        enemyAttack =1;
      }
      else if(enemy.DifenseOrAtack() <= 3)
      {
        if(plyerattack == 1 && !Steallife && !ranDmg)
        {
          cout<<Name<<" Trying Attack to The Enemy"<<enemyNum<<"\n";
          cout<<"====================================================================================================================\n";
          int dmg = kratos.addDamage();
          enemy.TakeDamage(dmg);
          cout<<"Enemy "<<enemyNum<<" Fail To Block The Attack \n";
          cout<<Name<<" Deals A Damage Of "<<dmg<<" To the Enemy "<<enemyNum<<"! \n";
          cout<<"Enemy "<<enemyNum<<"'s Health is: "<<enemy.GetP_Health()<<"\n\n";
        }
        if(plyerRange == 0 && Steallife)
        {
          cout<<Name<<" Trying Attack to The Enemy"<<enemyNum<<"\n";
          cout<<"====================================================================================================================\n";
          int dmg = kratos.addDamage();
          enemy.TakeDamage(dmg);
          cout<<"Enemy "<<enemyNum<<" Fail To Block The Ranged Attack \n";
          cout<<Name<<" Deals A Damage Of "<<dmg<<" To the Enemy "<<enemyNum<<"! \n";
          cout<<"Enemy "<<enemyNum<<"'s Health is: "<<enemy.GetP_Health()<<"\n\n";
        }
        
        enemyAttack = 1;
      }
      enemyAttack = 1;
      enemyTurn = true;
    }
  cout<<WHITE;
  return enemyAttack;
}


void choiceOption()
{
   if(!block)
        cout<<"Presh 'H' to Eat Jadi Butti For Healing or Press 'A' to Attack The opponent \n";
  else if(block && !ranDmg)
        cout<<"Press 'H' to use Healing Butti or 'A' to Attack the opponent or 'B' to Block the Opponent's Attack \n";
   else if(block && ranDmg)
        cout<<"Press 'H' to use Healing Butti or 'A' to Attack the opponent or 'B' to Block the Opponent's Attack or 'R' to use Ranged Attack \n";
 
}

// PLAYER ATTACK 
void PlayerTakingDmg(Kratos &kratos,Enemy &enemy,Boss &boss,int *plyerAttack,int *plyerRange,int enemyAttack,int bossAttack, int bossSplAttack, int enemyNum)
{
  cout<<MAGENTA;
  char playerInput;
  int dmg = 0;
  while(kratos.GetP_Health() >= 0 && boss.GetP_Health() >= 0 && enemy.GetP_Health() >= 0 && tolower(playerInput) != 'h' && tolower(playerInput) != 'a' && tolower(playerInput) !='b'&& 
 tolower(playerInput) !='r' )
{
      cout<<"=======================================================================================================================\n\n";
      cout<<Name<<"'s Turn: \n"<<WHITE;
      choiceOption();
      cout<<"Player input: \n";
      cin>>playerInput;
      cout<<RED;
      switch(tolower(playerInput)){
        case 'h':
          if(enemyAttack == 1 )
          {
            dmg = enemy.addDamage();
            kratos.PlayerHealing();
            cout<<RED;
            cout<<"Enemy "<<enemyNum<<" deals a damage of: "<<dmg<<" to "<<Name<<"! \n";
            kratos.TakeDamage(dmg);
            cout<<Name<<"'s Health: "<<kratos.GetP_Health()<<"\n\n";
          }
          else if(bossAttack == 1)
          {
            cout<<"MURLOC's Turn: \n";
            cout<<"MURLOC Is Trying To Attack! "<<endl;
            dmg = boss.addDamage();
            kratos.PlayerHealing();
            cout<<RED;
            cout<<"MURLOC deals a damge of: "<<dmg<<" to "<<Name<<"! \n";
            kratos.TakeDamage(dmg);
            cout<<Name<<"'s Health is: "<<kratos.GetP_Health()<<"\n\n";
          }
          else
          {
            kratos.PlayerHealing();
            cout<<Name<<"'s Health is: "<<kratos.GetP_Health()<<"\n\n";
          }
          break;
        case 'a':
          *plyerAttack = 1;
            if(enemyAttack == 1)
            {
              cout<<"Enemy "<<enemyNum<<"'s Turn \n";
              cout<<"Enemy "<<enemyNum<<" is Trying To Attack \n";
             cout<<"====================================================================================================================\n"; 
              dmg = enemy.addDamage();
              kratos.TakeDamage(dmg);
              cout<<Name<<"'s fail to block Enemy "<<enemyNum<<" Attack \n";
              cout<<"Enemy "<<enemyNum<<" deals a damage of "<<dmg<<" to "<<Name<<"! \n";
              cout<<Name<<"'s Health is: "<<kratos.GetP_Health()<<"\n\n";
            }
            else if(bossAttack == 1 )
            {
              cout<<"MURLOC's Turn: \n";
              cout<<"MURLOC is Trying To Use Ground Slash Ability! \n";
            cout<<"====================================================================================================================\n"; 
              dmg =boss.addDamage();
              kratos.TakeDamage(dmg);
              cout<<Name<<"'s fail to block MURLOC Attack \n"<<RED;
              cout<<"MURLOC  deals a damage of "<<dmg<<" to "<<Name<<"! \n";
              cout<<Name<<"'s Health is: "<<kratos.GetP_Health()<<"\n\n";
            }
            else if(bossSplAttack == 1)
            {
               cout<<"MURLOC's Turn: \n";
               cout<<"MURLOC is Trying To Use Ground Slash Ability! \n";
             cout<<"====================================================================================================================\n"; 
              dmg = boss.GroundSlash();
              kratos.TakeDamage(dmg);
              cout<<Name<<"'s fail to block MURLOC Special Attack \n"<<RED;
              cout<<"MURLOC  deals a damage of "<<dmg<<" to "<<Name<<"! \n";
              cout<<Name<<"'s Health is: "<<kratos.GetP_Health()<<"\n\n";
            }
            break;
        case 'b':
            if(block)
            {
              if(enemyAttack ==1 || bossAttack == 1)
              {
                cout<<Name<<"'s Blocked The Opponent Attack!\n"; 
              }
              else if(bossSplAttack == 1)
              {
                cout<<Name<<" can't Block the MURLOC's special attack! \n";
                dmg = boss.GroundSlash();
                kratos.TakeDamage(dmg);
                cout<<RED;
                cout<<"MURLOC deals a damage of: "<<dmg<<" to "<<Name<<"! \n"<<GREEN;
                cout<<Name<<"'s Health: "<<kratos.GetP_Health()<<"\n\n";
              }
              else if(enemyAttack == 0|| bossAttack == 0||bossSplAttack == 0)
              {
                cout<<"Enemy is not Attacking! You can't use Block! \n";
              }
            }
              else if(!ranDmg)
            {
              cout<<"Ranged Attack is Not Unlocked Yet! \n";
              plyerRange =0;
            }
            break;
          
        case 'r':
          
            if(ranDmg)
            {
              if(enemyAttack == 1)
              {
                int dmg = enemy.addDamage();
                kratos.TakeDamage(dmg);
                   cout<<Name<<" fails to block the Enemy "<<enemyNum<<"'s attack "<<endl<<RED;
            cout<<"Enemy "<<enemyNum<<" deals a damage of: "<<dmg<<" to "<<Name<<"! "<<endl<<GREEN;
            cout<<Name<<"'s Health: "<<kratos.GetP_Health()<<endl<<endl;
              }
              if(bossAttack == 1)
              {
                dmg = boss.addDamage();
                kratos.TakeDamage(dmg);
                 cout<<Name<<" fails to block the MURLOC's attack "<<endl<<RED;
            cout<<"MURLOC deals a damage of: "<<dmg<<" to "<<Name<<"! "<<endl<<GREEN;
            cout<<Name<<"'s Health: "<<kratos.GetP_Health()<<endl<<endl;
              }
              else if(bossSplAttack == 1)
              {
                dmg = boss.GroundSlash();
                kratos.TakeDamage(dmg);
                 cout<<"\t"<<Name<<" fails to block the MURLOC's special attack "<<endl<<RED;
            cout<<"MURLOC deals a damage of: "<<dmg<<" to "<<Name<<"! "<<endl<<GREEN;
            cout<<Name<<"'s Health: "<<kratos.GetP_Health()<<endl<<endl;
              }
              cout<<Name<<" is Trying to use Ranged attack !\n";
              *plyerRange =1;
            }
            else if(!ranDmg)
            {
              cout<<"Ranged Attack Is Not Unlocked yet! \n";
              *plyerRange = 0;
            }
            break;
          
        default:
          
            cout<<"Enter Valid Option\n";
            break;
          

      }
    }
  cout<<WHITE;
}

// GAME BATTLE LOOP
void  battleLoop(int enemyNum,int level)
{
  cout<<CLRSCR;
  char playerInput;
  int plyerAtack, plyerRange, bossSpAttack;
  int enemyAttack = 0, bossAttack = 0;
  
  Kratos kratos;
  Enemy enemy ;
  Boss boss;
  while(kratos.GetP_Health() > 0  && enemy.GetP_Health() > 0 && boss.GetP_Health() > 0 )
    {
      bool enemyTurn = false;
     PlayerTakingDmg(kratos, enemy, boss, &plyerAtack, &plyerRange, enemyAttack, bossAttack, bossSpAttack, enemyNum);
      if(kratos.GetP_Health() <= 0)
      {
        cout<<WHITE;
        cout<<"\n\n\t\t\t\t============= YOU ARE DEAD!!! ================\n\n";
        player1 = 1;
        enemy1 = enemy2 = enemy3 = enemy4 = enemy5 = boss1 = 0;
        
        break;
      }
      else 
      {
        enemyAttack = 0;
        bossAttack = 0;
        bossSpAttack = 0;
        playerInput = 'x';
        //Print();
        if(level == 6)
          bossAttack = PlayerAttacktoboss(boss.DifenseOrGroundSlash(),&bossSpAttack,plyerAtack,plyerRange,enemyTurn,kratos,boss);
        else
          enemyAttack = PlayerAttacktoEnemy(enemy.DifenseOrAtack(),plyerAtack,plyerRange,enemyNum,enemyTurn,kratos,enemy);
        plyerAtack = 0;
        plyerRange = 0;
        Print();
      }
      
    }
  if(enemy.GetP_Health() <= 0)
  {
    cout<<RED;
    cout<<"Enemy "<<enemyNum<<" Defeated! \n\n";
    switch(enemyNum)
      {
        case 1:
        enemy1 = 1;
        //b1 = 1;
        break;
        case 2:
        enemy2 = 1;
        break;
        case 3:
        enemy3 = 1;
        break;
        case 4:
        enemy4 = 1;
        break;
        case 5:
        enemy5 = 1;
        break;
        default:
        break;
        
      }
    if(level == 1 && enemy1 ==1)
    {
      cout<<MAGENTA;
      cout<<Name<<" Got A 'MAP'!\n\n";
      Map = true;
      Unlockedlv(level);
    }
    if(level == 2 && enemy1 == 1 && enemy2 == 1)
    {
      cout<<MAGENTA;
      cout<<Name<<" Got A 'SWORD'!\n\n";
      sword = true;
      C_hit = true;
      cout<<Name<<" Can now give Critical Hits to the Enemies \n\n";
      Unlockedlv(level);
    }
    if(level == 3 && enemy1 == 1&& enemy2 == 1 && enemy3 == 1)
    {
      cout<<MAGENTA;
      cout<<Name<<" Got A 'SHIELD'!\n\n";
      shield = true;
      block = true;
      cout<<Name<<" Can now Block the Enemy Attacks \n\n"; 
      Unlockedlv(level);
      
    }
    if(level == 4 && enemy1 == 1 && enemy2 == 1 && enemy3 == 1&& enemy4==1)
    {
      cout<<MAGENTA;
      cout<<Name<<" Got A 'ARMOUR'!\n\n";
      armour = true;
      Steallife =true;
      cout<<Name<<" Unlocks the ability of Life Steal \n\n"; 
      Unlockedlv(level);
    }
    if(level == 5 && enemy1 == 1 && enemy2 == 1&& enemy3 == 1&& enemy4==1 && enemy5 == 1)
    {
      cout<<MAGENTA;
      cout<<Name<<" Got A 'BOW'!\n\n";
      bow = true;
      ranDmg = true;
      cout<<Name<<" Can now perform Ranged Attacks \n\n"; 
      Unlockedlv(level);
    }
   
    EnemySlection(level);
    cout<<WHITE;
  }
  if(boss.GetP_Health() <= 0)
  {
    cout<<RED;
    cout<<"Boss "<<enemyNum<<" Defeated\n";
    boss1 =1;
    player1 = 0;
   
     if(level == 6 && boss1 == 1)
    {
      cout<<MAGENTA;
      cout<<CLRSCR;
      cout<<" YOU DEFEATED MURLOC!!!!\n\n"; 
      sleep(3);
        cout<<" YOU FREE THE PRINCES INDUMATI AND PEOPLE TO MURLOC THE PRISON \n\n";
      sleep(10);
      exit(0);
    }
  }
  
  
}


// LEVEL LOAD
void LoadLevel(int levelNum)
{
  if(levelNum == 6){
  
    cout<<"======================= LODING BOSS LEVEL ======================\n\n";
    sleep(3);
    cout<<CLRSCR;
  EnemySlection(6);
    }
  else{
    cout<<"=======================LOADING LEVEL "<<levelNum<<" ======================\n\n";
  sleep(3);
  cout<<CLRSCR;
  EnemySlection(levelNum);
    }
}


void SlectLevel()
{
  cout<<WHITE;

  int lv;
  cout<<"============================== LEVEL SLECTION ===============================\n\n\n";
  cout<<"\t\tSelect A Level! \n\n";
  cout<<"\t\tPress 1. TO LEVEL 1 ! \n";
  cout<<"\t\tPress 2. TO LEVEL 2 ! \n";
  cout<<"\t\tPress 3. TO LEVEL 3 ! \n";
  cout<<"\t\tPress 4. TO LEVEL 4 ! \n";
  cout<<"\t\tPress 5. TO LEVEL 5 ! \n";
  cout<<"\t\tPress 6. TO LEVEL 6 (THE BOSS LEVEL)! \n\n";
  cin>>lv;
  switch(lv)
    {
      case 1:
        {
          LoadLevel(1);
          break;
        }
      case 2:
        {
          if(Map)
            LoadLevel(2);
          else
            Lockedlv();
          break;
        }
      case 3:
        {
          if(sword)
            LoadLevel(3);
          else
            Lockedlv();
          break;
        }
      case 4:
        {
          if(shield)
            LoadLevel(4);
          else
            Lockedlv();
          break;
        }
      case 5:
        {
          if(armour)
            LoadLevel(5);
          else
            Lockedlv();
          break;
        }
      case 6:
        {
          if(bow)
            LoadLevel(6);
          else
            Lockedlv();
          break;
        }
      default:
        {
          cout<<" Please Choose Correct Level Number!\n";
          break;
        }
    }
}


// GAME STORY
void GameStory()
{
  cout<<MAGENTA;
  bool b = true;
  char rp;
  cout<<"================================================== GAME STORY =======================================================\n\n";
  cout<<"My name is "<<Name<<" and I am monster hunter I was going back to home town, \nWhen I got a message from a Baba on the way, who is a very big doctor in Dholakpur village. \nBaba tells me that a demon named Murlok attacked in his village. \nAnd killed some of the villagers and took some with him, \nOne of them also took Indumati, \nThe daughter of King Indravarma to that village. \nBaba took me to the king and the king told me to bring back my daughter and I will reward you. \n\n";
  cout<<"====================================================================================================================\n";
  sleep(3);
  while(b)
    {
      cout<<"Would you like to help him? (Y/N) \n";
      cout<<Name<<" Replied:- \n";
      cin>>rp;
      cout<<"\n";
      if(tolower(rp)== 'y')
      {
        cout<<WHITE;
        cout<<"You are a true Warrior!\n\n"<<MAGENTA;
        b = false;
      }
      else{
        cout<<WHITE;
        cout<<"Don't be a coward Help him! \n\n"<<MAGENTA;
      }
    }
  cout<<"=======================================================================================================================\n\n";
  cout<<"That man replied - THANK YOU SO MUCH!\n";
  cout<<"But you will need some magical items - MAP, SWORD, SHIELD, ARMOUR, BOW in order to defeat the Demon King!\n";
  cout<<"And you have to complete the 5 Levels to reach the Demon King, which are full of Demons \n";
  cout<<"You will get magical items once you complete a level, which will help you to defeat the Demon King \n\n";
  cout<<"Now Your New Journey Begins! \n";
  cout<<"=======================================================================================================================\n";
  cout<<"GAME PLYERS STATS \n";
  cout<<"=======================================================================================================================\n";
  cout<<Name<<"'s Health is 200 \n"<<Name<<"'s Mellee Damage is 23 - 15\n"<<Name<<"'s If You Have Armour Health Increase By 50 \n"<<Name<<"'s if you have sword The damage increase by 10\n";
  cout<<"=======================================================================================================================\n";
  cout<<"Every Enemy  Health is 80\nEvery Enemy mellee Damage is 20 - 6 \n";
  cout<<"=======================================================================================================================\n";
  cout<<"Murloc Health 250\nMurloc mellee Damage is 23 - 15\nMurloc have Graounslsh Abilty This Abilty Increase The damage by 10 point\nMurloc Have Another Healing Ability his healup by 5 % of TakeDamage\n";
  cout<<"=======================================================================================================================\n\n";
  cout<<"Please Wait 30 second To Enter Level Selection Menu!\n\n";
  sleep(30);
  cout<<WHITE;
}


//GAME MENU 
void GameIntro()
{
  cout << CLRSCR;
  cout<<"||\t\t\t\tMAIN MENU \t\t\t\t\t||"<<endl;
  cout<<"||\t\t\t\t          \t\t\t\t\t||\n";
  cout<<"||\t\t\tPress 1. START GAME\t\t\t\t|| "<<endl;
  cout<<"||\t\t\tPress 2. GAME RULES\t\t\t\t||"<<endl;
  cout<<"||\t\t\tPress 3. GAME EXIT \t\t\t\t||"<<endl<<endl;
  cin>>intro;
  switch(intro){
    case 1:{
      cout<<CLRSCR;
      cout<<"=======================================================================================================================\n\n";
      cout<<"Enter Your Character's Name: "<<endl;
      cin>>Name;
      cout<<CLRSCR;
      GameStory();
      cout<<CLRSCR;
     SlectLevel();
      break;
    }
    case 2:{
      bool ret = true;
      char back;
      while(ret){
        cout << CLRSCR;
        cout<<"==================================================== RULES ================================================= "<<endl;
        cout<<"1) There are total 6 levels in the game."<<endl;
        cout<<"2) There are multiple Enemies in each levels and you have to defeat all of them to complete the level."<<endl;
        cout<<"3) If the health of the player reaches 0, then the player will lose and the game will end."<<endl;
        cout<<"4) Player have many special abilities like critical damage, life steal, block, ranged attacks."<<endl;
        cout<<"5) Each special abilities will get unlock after completing a level."<<endl;
        cout<<"6) You can't block special attacks of enemies "<<endl;
        cout<<"7) You have to defeat the MURLOCK (Boss) to complete the game!"<<endl<<endl;
        cout<<"============================================================================================================\n";
        cout<<"Press B to go back to the Main Menu!!! "<<endl;
        cin>>back;
        if(tolower(back) == 'b'){
          GameIntro(); 
          ret = false;
        }
        else{
          cout<<"Please enter a valid option! "<<endl;
          sleep(2);
          cout<<CLRSCR;
        }
      }
      break;
    } 
    case 3:{
      char e;
      cout<<"Do you want to leave the game!!! ( Y/N )"<<endl;
      cin>>e;
      if(e == 'y' || e == 'Y'){
        cout<<"Game is closing"<<endl;
        sleep(2);
        exit(0);
      }
      else if(e == 'n' || e == 'N'){
        cout<<"Taking you back to the main menu"<<endl
            <<"Wait for some time"<<endl;
        sleep(2);
        GameIntro();
      }
    }
    default:{
      cout<<"Please enter a valid option! "<<endl;
      break;
    }
  }
}
void welcomeScreening()
{
  cout<<CLRSCR;
  cout<<"\n";
  cout<<"\n";
  cout<<"\n";
  cout<<"\n";
  cout<<"\n";
  cout<<"\t\t\t\t||=====================================================================||\n";
  cout<<"\t\t\t\t||=====================================================================||\n";
  cout<<"\t\t\t\t||                                                                     ||\n";
  cout<<"\t\t\t\t||                    WELCOME TO RPG ADVENTURE GAME                    ||\n";
  cout<<"\t\t\t\t||                                                                     ||\n";
  cout<<"\t\t\t\t||=====================================================================||\n";
  cout<<"\t\t\t\t||=====================================================================||\n\n\n";
  cout<<"\t\t\t\t||                   PLEASE WAIT GAME IS LOADING...                    ||\n\n";
  cout<<"\t\t\t\t||LOADING..............................................................||\n"; 
  sleep(5);
  cout<<CLRSCR;
}

int main()
{
  welcomeScreening();
  GameIntro();
}