#include "mainwindow.h"
#include "QToken.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QStack>
#include <QQueue>
#include <QDebug>
#include "QVariable.h"
#include "QTablaSemantica.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Analizador Lexico y Sintactico");
}
//Matriz
static int lexico [19][31]=
{
  {2,1,3,500,500,500,9,11,12,108,109,110,111,112,13,16,15,14,17,18,126,127,128,129,123,125,124,0,0,0,130},
  {2,1,2,2,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
  {2,2,2,2,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101},
  {102,102,3,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,4,102,102,102,102},
  {501,501,5,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501},
  {103,103,5,103,6,6,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103},
  {502,502,8,502,502,502,502,502,502,7,7,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502},
  {503,503,8,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503},
  {104,104,8,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104},
  {10,10,10,10,10,10,504,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
  {507,507,507,507,507,507,105,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507},
  {11,11,11,11,11,11,11,106,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
  {12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,107,12,12,12},
  {113,113,113,113,113,113,113,113,113,113,113,113,113,113,114,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113},
  {115,115,115,115,115,115,115,115,115,115,115,115,115,115,116,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115},
  {117,117,117,117,117,117,117,117,117,117,117,117,117,117,118,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117},
  {119,119,119,119,119,119,119,119,119,119,119,119,119,119,120,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119},
  {505,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505,121,505,505,505,505,505,505,505,505,505,505,505,505},
  {506,506,506,506,506,506,506,506,506,506,506,506,506,506,506,506,506,506,506,122,506,506,506,506,506,506,506,506,506,506,506}
};
static int sintactico[51][45]{
    /*0*/	{1   ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700 ,700},
    /*1*/	{701 ,3   ,2   ,2   ,2   ,2   ,2   ,701 ,701 ,2,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,701 ,2   ,701},
    /*2 aqui 4*/	{702 ,5   ,4   ,4   ,4   ,4   ,4   ,702 ,702 ,4   ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,702 ,4   ,702},
    /*3*/	{703 ,6   ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703 ,703},
    /*4*/	{704 ,704 ,7   ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704 ,704},
    /*5*/	{705 ,705 ,705 ,705 ,705 ,705 ,705 ,8   ,9   ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,705 ,9   ,705},
    /*6*/	{706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,10  ,11  ,12  ,13  ,14  ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706 ,706},
    /*7*/	{707 ,707 ,15  ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707 ,707},
    /*8*/	{708 ,708 ,708 ,708 ,708 ,708 ,708 ,16  ,16  ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,17  ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,708 ,16  ,708},
    /*9*/	{709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,18  ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709 ,709},
    /*10*/	{710 ,710 ,710 ,710 ,710 ,710 ,710 ,19  ,19  ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,20  ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,710 ,19  ,710},
    /*11*/	{711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,21  ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711 ,711},
    /*12*/	{712 ,712 ,22  ,22  ,22  ,22  ,22  ,712 ,712 ,23  ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712 ,712},
    /*13*/	{713 ,713 ,24  ,24  ,24  ,24  ,24  ,713 ,713 ,23  ,23  ,23  ,23  ,23  ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,713 ,23  ,713},
    /*14*/	{714 ,714 ,25  ,25  ,25  ,25  ,25  ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714 ,714},
    /*15*/	{715 ,715 ,26  ,27  ,28  ,29  ,30  ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715 ,715},
    /*16*/	{716 ,716 ,31  ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716 ,716},
    /*17*/	{717 ,717 ,32  ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717 ,717},
    /*18*/	{718 ,718 ,718 ,718 ,718 ,718 ,718 ,33  ,33  ,718 ,718 ,718 ,718 ,718 ,718 ,718 ,718 ,718 ,718 ,34  ,33  ,33  ,33  ,33  ,33  ,33  ,33  ,33  ,33  ,33  ,33  ,33  ,33  ,33  ,33  ,718 ,718 ,718 ,718 ,718 ,718 ,718 ,33  ,33  ,33 },
    /*19*/	{719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,35  ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719 ,719},
    /*20*/	{720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,36  ,34  ,720 ,720 ,720 ,720 ,720 ,720 ,720 ,36  ,720},
    /*21*/	{721 ,721 ,721 ,721 ,721 ,721 ,721 ,37  ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,38  ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,721 ,38  ,721},
    /*22*/	{722 ,722 ,39  ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,722 ,39  ,39  ,39  ,39  ,39  ,39  ,39  ,39  ,722 ,722},
    /*23*/	{723 ,723 ,723 ,723 ,723 ,723 ,723 ,41  ,41  ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,40  ,41  ,723 ,723 ,723 ,723 ,723 ,723 ,723 ,41  ,41  ,41 },
    /*24*/	{724 ,724 ,42  ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,724 ,42  ,42  ,42  ,42  ,42  ,42  ,42  ,724 ,724 ,724},
    /*25*/	{725 ,725 ,725 ,725 ,725 ,725 ,725 ,44  ,44  ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,725 ,43  ,44  ,44  ,44  ,725 ,725 ,725 ,725 ,725 ,725 ,44  ,44  ,44 },
    /*26*/	{726 ,726 ,45  ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,726 ,45  ,45  ,45  ,45  ,45  ,45  ,45  ,726 ,726 ,726},
    /*27*/	{727 ,727 ,47  ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,727 ,46  ,47  ,47  ,47  ,47  ,47  ,47  ,47  ,47  ,727},
    /*28*/	{728 ,728 ,48  ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,728 ,48  ,48  ,48  ,48  ,48  ,48  ,728 ,728 ,728},
    /*29*/	{729 ,729 ,729 ,729 ,729 ,729 ,729 ,49  ,49  ,729 ,729 ,729 ,729 ,729 ,729 ,729 ,729 ,729 ,729 ,729 ,729 ,729 ,729 ,729 ,729 ,729 ,50  ,50  ,50  ,50  ,50  ,50  ,49  ,49  ,49  ,729 ,729 ,729 ,729 ,729 ,729 ,729 ,49  ,49  ,49 },
    /*30*/	{730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,51  ,52  ,53  ,54  ,55  ,56  ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730 ,730},
    /*31*/	{731 ,731 ,57  ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,731 ,57  ,57  ,57  ,57  ,57  ,57  ,731 ,731 ,731},
    /*32*/	{732 ,732 ,732 ,732 ,732 ,732 ,732 ,58  ,58  ,732 ,732 ,732 ,732 ,732 ,732 ,732 ,732 ,732 ,732 ,732 ,732 ,732 ,732 ,732 ,59  ,59  ,58  ,58  ,58  ,58  ,58  ,58  ,58  ,58  ,58  ,732 ,732 ,732 ,732 ,732 ,732 ,732 ,58  ,58  ,58 },
    /*33*/	{733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,60  ,61  ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733 ,733},
    /*34*/	{734 ,734 ,62  ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,734 ,62  ,62  ,62  ,62  ,62  ,62  ,734 ,734 ,734},
    /*35*/	{735 ,735 ,735 ,735 ,735 ,735 ,735 ,63  ,63  ,735 ,735 ,735 ,735 ,735 ,735 ,735 ,735 ,735 ,735 ,735 ,735 ,64  ,64  ,64  ,63  ,63  ,63  ,63  ,63  ,63  ,63  ,63  ,63  ,63  ,63  ,735 ,735 ,735 ,735 ,735 ,735 ,735 ,63  ,63  ,63 },
    /*36*/	{736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,65  ,66  ,67  ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736 ,736},
    /*37*/	{737 ,737 ,68  ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,737 ,69  ,70  ,71  ,72  ,73  ,74  ,737 ,737 ,737},
    /*38*/	{738 ,738 ,738 ,75  ,75,75 ,75,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738 ,738},
    /*39*/	{739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,76  ,76  ,76  ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739 ,739},
    /*40*/	{740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,78  ,77  ,77  ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,740 ,78  ,740},
    /*41*/	{741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,80  ,79  ,79  ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,741 ,79  ,741},
    /*42*/	{742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,81  ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742 ,742},
    /*43*/	{743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,82  ,83  ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,743 ,83  ,743},
    /*44*/	{744 ,744 ,744 ,744 ,84  ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744 ,744},
    /*45*/	{745 ,745 ,745 ,745 ,745 ,85  ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745 ,745},
    /*46*/	{746 ,746 ,86  ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746 ,746},
    /*47*/	{747 ,747 ,747 ,747 ,747 ,747 ,747 ,87  ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,747 ,88  ,88  ,747},
    /*48*/	{748 ,748 ,748 ,748 ,748 ,748 ,89  ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748 ,748},
    /*49*/	{749 ,749 ,90  ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,749 ,90  ,90  ,90  ,90  ,90  ,90  ,90  ,90  ,749 ,749},
    /*50*/	{750 ,750 ,750 ,750 ,750 ,750 ,750 ,91  ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,750 ,92  ,92  ,750}
};


static QQueue<QToken> cola;
static QStack<int> pila;

static QString tiposMSR[5][5]={
    {"int"  ,"float","x"   ,"x"     ,"x"},
    {"float","float","x"   ,"x"     ,"x"},
    {"x"    ,"x"    ,"x"   ,"x"     ,"x"},
    {"x"    ,"x"    ,"x"   ,"string","x"},
    {"x"    ,"x"    ,"x"   ,"x"     ,"x"},
};
static QString tipoAsignacion[5][5]={
    {"int"  ,"x"    ,"x"   ,"x"     ,"x"},
    {"x"    ,"float","x"   ,"x"     ,"x"},
    {"x"    ,"x"    ,"char","x"     ,"x"},
    {"x"    ,"x"    ,"x"   ,"string","x"},
    {"x"    ,"x"    ,"x"   ,"x"     ,"bool"},
};
static QString tiposDiv[5][5]={
    {"float"  ,"float","x","x","x"},
    {"float","float"  ,"x","x","x"},
    {"x"    ,"x"      ,"x","x","x"},
    {"x"    ,"x"      ,"x","x","x"},
    {"x"    ,"x"      ,"x","x","x"},
};
static QQueue<QVariable> tablaSemantica;
static QTablaSemantica TablaCuadruplos;
static int contadorVariSemantico=0;
static int contadorTemporales=1;
static QStack<QString> pila_operandos;
static QStack<QString> pila_operadores;
static QStack<QString> pila_tipos;
static QStack<int> pila_saltos;
static QString MarcaFondoFalso = "MFF";
//Descontructor
MainWindow::~MainWindow()
{
    delete ui;
}
//Evento de botton
void MainWindow::on_pushButton_clicked()
{
    ui->tabla->setRowCount(0);
    pila.clear();
    pila.append(0);
    cola.clear();
    TablaCuadruplos.contador=0;
    TablaCuadruplos.limpiarTabla();
    contadorVariSemantico=0;
    contadorTemporales=1;
    tablaSemantica.clear();
    pila_saltos.clear();
    pila_operandos.clear();
    pila_tipos.clear();
    pila_operadores.clear();
    analiza();
    AnalizadorSintactico();
    insertarDatoEnTablaCuadruplos();
}
void MainWindow::insertarDatoEnTabla(QString numero,QString token, QString descripcion){
    ui->tabla->insertRow(ui->tabla->rowCount());
    int row=ui->tabla->rowCount()-1;
    ui->tabla->setItem(row,0,new QTableWidgetItem(numero));
    ui->tabla->setItem(row,1,new QTableWidgetItem(token));
    ui->tabla->setItem(row,2,new QTableWidgetItem(descripcion));
}
void MainWindow::insertarDatoEnTablaCuadruplos(){
   QQueue<QCuadruplo> cola=TablaCuadruplos.getTabla();
   for (int var=0;var < cola.size();++var) {
       ui->tablaCuadruplos->insertRow(ui->tablaCuadruplos->rowCount());
       int row=ui->tablaCuadruplos->rowCount()-1;
       ui->tablaCuadruplos->setItem(row,0,new QTableWidgetItem(QString::number(var+1)));
       ui->tablaCuadruplos->setItem(row,1,new QTableWidgetItem(cola.value(var).getOperando()));
       ui->tablaCuadruplos->setItem(row,2,new QTableWidgetItem(cola.value(var).getOperador1()));
       ui->tablaCuadruplos->setItem(row,3,new QTableWidgetItem(cola.value(var).getOperador2()));
       ui->tablaCuadruplos->setItem(row,4,new QTableWidgetItem(cola.value(var).getResultado()));
   }
}
void MainWindow::insertarDatoEnTablaError(QString numero, QString token, QString descripcion){
    ui->tablaErrores->insertRow(ui->tablaErrores->rowCount());
    int row=ui->tablaErrores->rowCount()-1;
    ui->tablaErrores->setItem(row,0,new QTableWidgetItem(numero));
    ui->tablaErrores->setItem(row,1,new QTableWidgetItem(token));
    ui->tablaErrores->setItem(row,2,new QTableWidgetItem(descripcion));

}
void MainWindow::on_actionAbrir_triggered()
{
    QFile archivo;
    QTextStream io;
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,"Abrir","","Archivos ISC(*.ISC)");
    if(nombreArchivo.isEmpty())
        return;
    archivo.setFileName(nombreArchivo);
    archivo.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!archivo.isOpen()){
        QMessageBox::critical(this,"Error",archivo.errorString());
    }
    io.setDevice(&archivo);
    ui->TextoAnalizar->setPlainText(io.readAll());
    archivo.flush();
    archivo.close();
}
void MainWindow::on_actionGuardar_triggered()
{
    QFile archivo;
    QTextStream io;
    QString nombreAchivo;
    nombreAchivo=QFileDialog::getSaveFileName(this,"Guardar","","Archivos ISC(*.ISC)");
    if(nombreAchivo.isEmpty())
        return;
    archivo.setFileName(nombreAchivo);
    archivo.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!archivo.isOpen()){
        QMessageBox::critical(this,"Error", archivo.errorString());
        return;
    }
    io.setDevice(&archivo);
    io<<ui->TextoAnalizar->toPlainText();
    archivo.close();
}
void MainWindow::analiza(){
    int edo=0,col;
    int contador=0;
    QChar car;
    QString tokens="";
    QString texto;
    bool bandera = true;
    while(bandera)
    {
            texto=ui->TextoAnalizar->toPlainText()+" ";
            car=texto.at(contador);
            col=Relaciona(car);
            edo=lexico[edo][col];
            contador++;
            tokens+=car;
        if (edo>99&& edo<131){
            if(edo ==100 || edo == 101  || edo == 102|| edo == 103 || edo == 113 || edo == 117|| edo == 115 || edo == 119){
                tokens.chop(1);
                contador--;
            }
            Token(tokens,edo);
            tokens="";
            edo=0;
        }
        if(edo >= 500 && edo <= 510){
            Error(tokens,edo);
            edo=0;
        }
        if(contador >= texto.length()){
            bandera=false;
        }
    }
}
void MainWindow::on_pushButton_2_clicked()
{


}
int MainWindow::Relaciona(QChar car)
{
    if (car>='A' && car<='Z')
        return 0;
    else if (car >='a' && car <='z')
        return 1;
    else if (car >='0' && car <='9')
        return 2;
    else if (car =='_')
        return 3;
    else if (car =='E')
        return 4;
    else if (car =='e')
        return 5;
    else if (car =='\'')
        return 6;
    else if (car =='"')
        return 7;
    else if (car =='#')
        return 8;
    else if (car =='+')
        return 9;
    else if (car =='-')
        return 10;
    else if (car =='*')
        return 11;
    else if (car =='/')
        return 12;
    else if (car =='%')
        return 13;
    else if (car =='=')
        return 14;
    else if (car =='>')
        return 15;
    else if (car =='<')
        return 16;
    else if (car =='!')
        return 17;
    else if (car =='&')
        return 18;
    else if (car =='|')
        return 19;
    else if (car =='(')
        return 20;
    else if (car ==')')
        return 21;
    else if (car =='[')
        return 22;
    else if (car ==']')
        return 23;
    else if (car ==':')
        return 24;
    else if (car ==';')
        return 25;
    else if (car =='.')
        return 26;
    else if (car =='\n')
        return 27;
    else if (car =='\t')
        return 28;
    else if (car ==' ')
        return 29;
    else if (car ==',')
        return 30;
}
void MainWindow::Token(QString token,int e){
    QString estado=QString::number(e);
    QString recorte =token.simplified();
    QToken tokenSint = QToken(recorte);
    switch (e) {
        case 100:{
            if (recorte == "holyd" || recorte == "define"|| recorte == "if"|| recorte == "while"
                    || recorte == "read"|| recorte == "write"|| recorte == "finish"|| recorte == "elihw"
                    || recorte == "elseif"|| recorte == "else"|| recorte == "fi"|| recorte == "int"
                    || recorte == "float"|| recorte == "char"|| recorte == "string"|| recorte == "bool"){
                insertarDatoEnTabla(estado,recorte,"Palabra reservada");
                if(recorte=="holyd") { tokenSint.setEstado(1000);cola.enqueue(tokenSint);}
                else if (recorte=="define"){ tokenSint.setEstado(1001); cola.enqueue(tokenSint);}
                else if (recorte=="if")   { tokenSint.setEstado(1003); cola.enqueue(tokenSint);}
                else if (recorte=="while"){tokenSint.setEstado(1004);cola.enqueue(tokenSint);}
                else if (recorte=="read"){tokenSint.setEstado(1005);cola.enqueue(tokenSint);}
                else if (recorte=="write"){tokenSint.setEstado(1006);cola.enqueue(tokenSint);}
                else if (recorte=="finish"){tokenSint.setEstado(1009);cola.enqueue(tokenSint);}
                else if (recorte=="elihw"){tokenSint.setEstado(1010);cola.enqueue(tokenSint);}
                else if (recorte=="elseif"){tokenSint.setEstado(1011);cola.enqueue(tokenSint);}
                else if (recorte=="else"){tokenSint.setEstado(1012);cola.enqueue(tokenSint);}
                else if (recorte=="fi"){tokenSint.setEstado(1013);cola.enqueue(tokenSint);}
                else if (recorte=="int"){tokenSint.setEstado(1014);cola.enqueue(tokenSint);}
                else if (recorte=="float"){tokenSint.setEstado(1015);cola.enqueue(tokenSint);}
                else if (recorte=="char"){tokenSint.setEstado(1016);cola.enqueue(tokenSint);}
                else if (recorte=="string"){tokenSint.setEstado(1017);cola.enqueue(tokenSint);}
                else if (recorte=="bool"){tokenSint.setEstado(1018);cola.enqueue(tokenSint);}
            }else {
                insertarDatoEnTabla(estado,recorte,"Identificador");
                tokenSint.setEstado(1002); cola.enqueue(tokenSint);
            }
            break;
        }
        case 101:{
            insertarDatoEnTabla(estado,recorte,"Palabra Mayuscula");
                    tokenSint.setEstado(1002);cola.enqueue(tokenSint);break;
        }
        case 102:insertarDatoEnTabla(estado,token,"Numero Entero"); tokenSint.setEstado(1036);cola.enqueue(tokenSint); break;
        case 103:insertarDatoEnTabla(estado,token,"Numero Decimal");tokenSint.setEstado(1037);cola.enqueue(tokenSint);    break;
        case 104:insertarDatoEnTabla(estado,token,"Notacion Cientifica");tokenSint.setEstado(1038);cola.enqueue(tokenSint); break;
        case 105:insertarDatoEnTabla(estado,token,"Constante Caracteres");tokenSint.setEstado(1039);cola.enqueue(tokenSint); break;
        case 106:insertarDatoEnTabla(estado,token,"Constante Cadena"); tokenSint.setEstado(1040);cola.enqueue(tokenSint);break;
        case 107:insertarDatoEnTabla(estado,token,"Constante Comentario"); break;
        case 108:insertarDatoEnTabla(estado,token,"Suma");tokenSint.setEstado(1024);cola.enqueue(tokenSint); break;
        case 109:insertarDatoEnTabla(estado,token,"Resta");tokenSint.setEstado(1025);cola.enqueue(tokenSint); break;
        case 110:insertarDatoEnTabla(estado,token,"Multiplicacion");tokenSint.setEstado(1021);cola.enqueue(tokenSint); break;
        case 111:insertarDatoEnTabla(estado,token,"Division");tokenSint.setEstado(1022);cola.enqueue(tokenSint); break;
        case 112:insertarDatoEnTabla(estado,token,"Modulo");tokenSint.setEstado(1023); cola.enqueue(tokenSint);break;
        case 113:insertarDatoEnTabla(estado,token,"Asignacion");tokenSint.setEstado(1020);cola.enqueue(tokenSint); break;
        case 114:insertarDatoEnTabla(estado,token,"Igual");tokenSint.setEstado(1026); cola.enqueue(tokenSint);break;
        case 115:insertarDatoEnTabla(estado,token,"Negacion"); tokenSint.setEstado(1035);cola.enqueue(tokenSint);break;
        case 116:insertarDatoEnTabla(estado,token,"Diferencia de Numero");tokenSint.setEstado(1027); cola.enqueue(tokenSint);break;
        case 117:insertarDatoEnTabla(estado,token,"Menor"); tokenSint.setEstado(1028);cola.enqueue(tokenSint);break;
        case 118:insertarDatoEnTabla(estado,token,"Menor Igual");tokenSint.setEstado(1029); cola.enqueue(tokenSint);break;
        case 119:insertarDatoEnTabla(estado,token,"Mayor"); tokenSint.setEstado(1030);cola.enqueue(tokenSint);break;
        case 120:insertarDatoEnTabla(estado,token,"Mayor Igual");tokenSint.setEstado(1031);cola.enqueue(1031); break;
        case 121:insertarDatoEnTabla(estado,token,"AND");tokenSint.setEstado(1032); cola.enqueue(tokenSint); break;
        case 122:insertarDatoEnTabla(estado,token,"OR"); tokenSint.setEstado(1033);cola.enqueue(tokenSint);break;
        case 123:insertarDatoEnTabla(estado,token,"Dos Puntos");tokenSint.setEstado(1008);cola.enqueue(tokenSint); break;
        case 124:insertarDatoEnTabla(estado,token,"Punto"); break;
        case 125:insertarDatoEnTabla(estado,token,"Punto y coma");tokenSint.setEstado(1044);cola.enqueue(tokenSint); break;
        case 126:insertarDatoEnTabla(estado,token,"Abre Parentesis");tokenSint.setEstado(1041);cola.enqueue(tokenSint); break;
        case 127:insertarDatoEnTabla(estado,token,"Cierra Parentesis");tokenSint.setEstado(1042); cola.enqueue(tokenSint);break;
        case 128:insertarDatoEnTabla(estado,token,"Abre Corchete");tokenSint.setEstado(1019); cola.enqueue(tokenSint);break;
        case 129:insertarDatoEnTabla(estado,token,"Cierra Corchete"); tokenSint.setEstado(1034);cola.enqueue(tokenSint);break;
        case 130:insertarDatoEnTabla(estado,token,"Coma"); tokenSint.setEstado(1007); cola.enqueue(tokenSint);;
    }

}
void MainWindow::Error(QString token, int e){
    QString ed=QString::number(e);
    switch (e) {
        case 500: insertarDatoEnTablaError(ed,token,"Caracter Invalido"); break;
        case 501: insertarDatoEnTablaError(ed,token,"Punto Repetido"); break;
        case 502: insertarDatoEnTablaError(ed,token,"Letra E|e repetida "); break;
        case 503: insertarDatoEnTablaError(ed,token,"Notacion Cientifica No valida"); break;
        case 504: insertarDatoEnTablaError(ed,token,"Apostrofe repetido"); break;
        case 505: insertarDatoEnTablaError(ed,token,"Operador '&' invalido"); break;
        case 506: insertarDatoEnTablaError(ed,token,"Operador '|' invalido"); break;
        case 507: insertarDatoEnTablaError(ed,token,"Apostrofe Repetido 2"); break;
    }
}
void MainWindow::AnalizadorSintactico(){
    if (cola.isEmpty()){
        QMessageBox::information(this,"Correcto","Sin errores de sintaxis");
    }else{
        if(pila.top()==1043){
            pila.pop();
            AnalizadorSintactico();
        }else {
            Semantico();//Semantico
            if(pila.top()==-1){
                return;
            }
            if (cola.head().getEstado()==pila.top()){
                pila.pop();
                cola.detach();
                cola.dequeue();
                AnalizadorSintactico();
            }else{
                //qDebug() << "Pila top: " << pila.top()<<" Cola Head: "<<cola.head().getEstado();
                int valor=TablaProducciones(sintactico[pila.top()][cola.head().getEstado()-1000]);
                //qDebug()<< "El valor de la tabla es: "<< valor;
                if (valor>699){
                    QMessageBox::critical(this,"Error","Error de sintaxis");
                }else{
                    AnalizadorSintactico();
                }
           }
        }
    }
}
void MainWindow::Semantico(){
    switch (pila.top()) {
    case 2000:{
        pila.pop();
        if (tablaSemantica.isEmpty()){
            QVariable var= QVariable(cola.head().getContenido(),"","");
            tablaSemantica.enqueue(var);
        }else{
            for (int var = 0; var < tablaSemantica.length(); ++var) {
                if(cola.head().getContenido() == tablaSemantica.value(var).getContenido()){
                    QMessageBox::critical(this, "Error","Variable Duplicada");
                    pila.append(-1);
                    break;
                    return;
                }
            }
            QVariable varl= QVariable(cola.head().getContenido(),"","");
            tablaSemantica.enqueue(varl);
        }
        break;
        }
    case 2001:{
        pila.pop();
        for (int var = contadorVariSemantico; var < tablaSemantica.size(); ++var){
            QVariable v= QVariable(tablaSemantica.value(var).getContenido(),"","int");
            tablaSemantica.replace(var,v);
            contadorVariSemantico++;
        }
        break;
    }
    case 2002:{
        pila.pop();
        for (int var = contadorVariSemantico; var < tablaSemantica.length(); ++var){
            QVariable v= QVariable(tablaSemantica.value(var).getContenido(),"","float");
            tablaSemantica.replace(var,v);
            contadorVariSemantico++;
        }
        break;
    }
    case 2003:{
        pila.pop();
        for (int var = contadorVariSemantico; var < tablaSemantica.length(); ++var){
            QVariable v= QVariable(tablaSemantica.value(var).getContenido(),"","char");
            tablaSemantica.replace(var,v);
            contadorVariSemantico++;
        }
        break;
        }
    case 2004:{
        pila.pop();
        for (int var = contadorVariSemantico; var < tablaSemantica.length(); ++var){
            QVariable v= QVariable(tablaSemantica.value(var).getContenido(),"","string");
            tablaSemantica.replace(var,v);
            contadorVariSemantico++;
        }
        break;
    }
    case 2005:{
        pila.pop();
        for (int var = contadorVariSemantico; var < tablaSemantica.length(); ++var){
            QVariable v= QVariable(tablaSemantica.value(var).getContenido(),"","bool");
            tablaSemantica.replace(var,v);
            contadorVariSemantico++;
        }
        break;
        }
    case 2006:{
        pila.pop();
        for (int var = 0; var < tablaSemantica.size(); ++var) {
            if(cola.head().getContenido() == tablaSemantica.value(var).getContenido()){
                pila_tipos.append(tablaSemantica.value(var).getTipo());
                //Codigo Intermedio
                pila_operandos.append(tablaSemantica.value(var).getContenido());
                return;
            }
        }
        QMessageBox::critical(this,"Error","No existe la variable");
        pila.append(-1);
        break;
    }
    case 2007:
        pila.pop();
        pila_operadores.push(cola.head().getContenido());
        break;
    case 2008:
        pila.pop();
        pila_tipos.append("int");
        pila_operandos.append(cola.head().getContenido());
        break;
    case 2009:
        pila.pop();
        pila_tipos.append("float");
        pila_operandos.append(cola.head().getContenido());
        break;
    case 2010:
        pila.pop();
        pila_tipos.append("int");//No sabemos
        pila_operandos.append(cola.head().getContenido());//no sabemos
        break;
    case 2011:
        pila.pop();
        pila_tipos.append("char");
        pila_operandos.append(cola.head().getContenido());
        break;
    case 2012:
        pila.pop();
        pila_tipos.append("string");
        pila_operandos.append(cola.head().getContenido());
        break;
    case 2013:
        pila.pop();
        pila_operadores.append(MarcaFondoFalso);
        break;
    case 2014:
        pila.pop();
        pila_operadores.pop();
        break;
    case 2015://Generar cuadruplo multiplicacion
        pila.pop();
        if(!pila_operadores.isEmpty()){
        if (pila_operadores.top() == "*" || pila_operadores.top() == "/" || pila_operadores.top() == "%") {
            QString nuevoTipo = validarTipos(pila_tipos.top(),pila_tipos.at(pila_tipos.length()-2),pila_operadores.top());
            if(nuevoTipo == "x"){
                QMessageBox::critical(this, "Error","Tipos no son permitidos ");
                return;
            }
            QString temporal = "Temp "+QString::number(contadorTemporales);
            TablaCuadruplos.InsertarCuadruplo(pila_operadores.top(),//Operador
                                              pila_operandos.at(pila_operandos.size()-2),//Operando1
                                              pila_operandos.top(),//Operando 2
                                              temporal);//Resultado
            contadorTemporales+=1;
            pila_tipos.pop();
            pila_tipos.pop();
            pila_operandos.pop();
            pila_operandos.pop();
            pila_operandos.append(temporal);
            pila_operadores.pop();
            pila_tipos.append(nuevoTipo);
        }
        if(pila_operadores.top() == "write"){
            TablaCuadruplos.InsertarRead(pila_operadores.top(), pila_operandos.top());
            pila_operandos.pop();
            pila_operadores.pop();
            pila_operadores.pop();
        }
        }
        break;
    case 2016:
        pila.pop();
        pila_operadores.append("*");
        break;
    case 2017:
        pila.pop();
        pila_operadores.append("/");
        break;
    case 2018:
        pila.pop();
        pila_operadores.append("%");
        break;
    case 2019://Generar cuadruplo suma
        pila.pop();
        if (!pila_operadores.isEmpty()){
        if (pila_operadores.top() == "+" || pila_operadores.top() == "-") {
            QString nuevoTipo = validarTipos(pila_tipos.top(),
                                pila_tipos.value(pila_tipos.length()-2), pila_operadores.top());
            if(nuevoTipo == "x"){
                QMessageBox::critical(this,"Error","Tipos no son permitidos ");
                return;
            }
            QString temporal = "Temp "+QString::number(contadorTemporales);
            TablaCuadruplos.InsertarCuadruplo(pila_operadores.top(),//Operador
                                              pila_operandos.at(pila_operandos.size()-2),//Operando1
                                              pila_operandos.top(),//Operando 2
                                              temporal);//Resultado
            contadorTemporales+=1;
            pila_tipos.pop();
            pila_tipos.pop();
            pila_operandos.pop();
            pila_operandos.pop();
            pila_operandos.append(temporal);
            pila_operadores.pop();
            pila_tipos.append(nuevoTipo);
        }
        }
        break;
    case 2020:
        pila.pop();
        pila_operadores.append("+");
        break;
    case 2021:
        pila.pop();
        pila_operadores.append("-");
        break;
    case 2022://Generar cuadruplo asignacion
        pila.pop();
        if (!pila_operadores.isEmpty()){
        if (pila_operadores.top() == "=") {
            QString nuevoTipo = validarTipos(pila_tipos.top(), pila_tipos.at(pila_tipos.length()-2), pila_operadores.top());
            if(nuevoTipo == "x"){
                QMessageBox::critical(this, "Error","Error entre tipos");
                return;
            }else if(nuevoTipo == MarcaFondoFalso){
                return;
            }
            TablaCuadruplos.InsertarCuadruplo(pila_operadores.top(),//Operador
                                              pila_operandos.at(pila_operandos.size()-2),//Operando1
                                              pila_operandos.top(),//Operando 2
                                              pila_operandos.top());//Resultado
            pila_tipos.pop();
            pila_tipos.pop();
            pila_operadores.pop();
            pila_tipos.append(nuevoTipo);
        }
        }
        break;
    case 2023://Empieza if
        pila.pop();
        pila_operadores.push(MarcaFondoFalso);
        break;
    case 2024:{
        pila.pop();
        QString temporal = "Temp "+QString::number(contadorTemporales);
        TablaCuadruplos.InsertarCuadruplo(pila_operadores.top(),//Operador
                                          pila_operandos.at(pila_operandos.size()-2),//Operando1
                                                  pila_operandos.top(),//Operando 2
                                          temporal);//Resultado
        contadorTemporales++;
        pila_operandos.pop();
        pila_operandos.pop();
        pila_operadores.pop();
        pila_operandos.append(temporal);
        break;
    }
    case 2025:
        pila.pop();
        pila_saltos.append(TablaCuadruplos.getContador());// Se apilo el 1
        TablaCuadruplos.InsertarCuadruploSF(TablaCuadruplos.getSaltoFalso(),pila_operandos.top());
        break;
    case 2026:
        pila.pop();
        TablaCuadruplos.InsertarCuadruploSI(TablaCuadruplos.getSaltoIncondicionar(),pila_operandos.top());
        qDebug()<<"Pila salto"<<pila_saltos.top();
        TablaCuadruplos.Rellenar(pila_saltos.top(),QString::number(TablaCuadruplos.getContador()+1));//Vamos a 1 a rellenar
        pila_saltos.pop();
        pila_saltos.append(TablaCuadruplos.getContador()-1);
        break;
    case 2027:
        pila.pop();
        TablaCuadruplos.Rellenar(pila_saltos.top(),QString::number(TablaCuadruplos.getContador()+1));
        pila_saltos.pop();
        break;
    case 2028:
        pila.pop();
        pila_operandos.pop();
        break;
    case 2029:
        pila.pop();
        pila_operadores.append("==");
        break;
    case 2030:
        pila.pop();
        pila_operadores.append("!=");
        break;
    case 2031:
        pila.pop();
        pila_operadores.append("<");
        break;
    case 2032:
        pila.pop();
        pila_operadores.append("<=");
        break;
    case 2033:
        pila.pop();
        pila_operadores.append(">");
        break;
    case 2034:
        pila.pop();
        pila_operadores.append(">=");
        break;
    case 2035://Empieza while
        pila.pop();
        pila_saltos.push(TablaCuadruplos.contador+1);
        pila_operadores.append(MarcaFondoFalso);
        break;
    case 2036:{
        pila.pop();
        QString temporal = "Temp "+QString::number(contadorTemporales);
        TablaCuadruplos.InsertarCuadruplo(pila_operadores.top(),//Operador
                                          pila_operandos.at(pila_operandos.size()-2),//Operando1
                                                  pila_operandos.top(),//Operando 2
                                          temporal);//Resultado
        contadorTemporales++;
        pila_operandos.pop();
        pila_operandos.pop();
        pila_operadores.pop();
        pila_operandos.append(temporal);
        }
        break;
    case 2037:
        pila.pop();
        pila_saltos.append(TablaCuadruplos.getContador());
        TablaCuadruplos.InsertarCuadruploSF(TablaCuadruplos.getSaltoFalso(),pila_operandos.top());
        break;
    case 2038:
        pila.pop();
        TablaCuadruplos.InsertarCuadruploSI(TablaCuadruplos.getSaltoIncondicionar(),QString::number(pila_saltos.at(pila.length()-2)));
        TablaCuadruplos.Rellenar(pila_saltos.top(),QString::number(TablaCuadruplos.getContador()+1));
        pila_saltos.pop();
        pila_saltos.pop();
        pila_saltos.append(TablaCuadruplos.getContador()-1);
        break;
    case 2039:
        pila.pop();
        pila_operadores.push(MarcaFondoFalso);
        pila_operadores.push(cola.head().getContenido());
        break;
    case 2040:
        pila.pop();
        TablaCuadruplos.InsertarRead(pila_operadores.top(),pila_operandos.top());
        pila_operandos.pop();
        pila_operadores.pop();
        pila_operadores.pop();
        pila_tipos.pop();
        break;
    case 2041:
        pila.pop();
        pila_operadores.push(MarcaFondoFalso);
        pila_operadores.push(cola.head().getContenido());
        break;

    }//final switch
}
QString MainWindow::validarTipos(QString tope, QString topeMenUno,QString signo){
    int row=tipoANumero(tope);
    int column=tipoANumero(topeMenUno);
    if (signo == MarcaFondoFalso)return MarcaFondoFalso;
    if (signo == "=")return tipoAsignacion[row][column];
    if (signo == "*" || signo == "+" || signo == "-")return tiposMSR[row][column];
    if (signo == "/")return tiposDiv[row][column];
}
int MainWindow::tipoANumero(QString tipo){
    if(tipo == "int")return 0;
    if(tipo == "float")return 1;
    if(tipo == "char")return 2;
    if(tipo == "string")return 3;
    if(tipo == "bool")return 4;
}
int MainWindow::TablaProducciones(int ubicacion){
    pila.pop();
    switch (ubicacion) {
    case 1:
        pila.append(1009);
        pila.append(12);
        pila.append(1);
        pila.append(1008);
        pila.append(1002);
        pila.append(1000);
        break;
    case 2:
        pila.append(1043);
        break;
    case 3:
        pila.append(2);
        pila.append(3);
        break;
    case 4:
        pila.append(1043);
        break;
    case 5:
        pila.append(1);break;
    case 6:
        pila.append(1044);
        pila.append(6);
        pila.append(1008);
        pila.append(4);
        pila.append(1001);
        break;
    case 7:
        pila.append(5);
        pila.append(7);break;
    case 8:
        pila.append(4);
        pila.append(1007);break;
    case 9:
        pila.append(1043);break;
    case 10://int
        pila.append(1014);
        pila.append(2001);
        break;
    case 11://float
        pila.append(1015);
        pila.append(2002);
        break;
    case 12://char
        pila.append(1016);
        pila.append(2003);
        break;
    case 13://string
        pila.append(1017);
        pila.append(2004);
        break;
    case 14://bool
        pila.append(1018);
        pila.append(2005);
        break;
    case 15:
        pila.append(8);
        pila.append(1002);
        pila.append(2000);
        break;
    case 16:
        pila.append(1043);break;
    case 17:
        pila.append(9);break;
    case 18:
        pila.append(10);
        pila.append(11);break;
    case 19:
        pila.append(1043);
        break;
    case 20:
        pila.append(9);break;
    case 21:
        pila.append(1034);
        pila.append(1036);
        pila.append(1019);break;
    case 22:
        pila.append(13);
        pila.append(14);
        break;
    case 23:
        pila.append(1043);
        break;
    case 24:
        pila.append(12);
        break;
    case 25:
        pila.append(1044);
        pila.append(15);
        break;
    case 26:
        pila.append(16);
        break;
    case 27:
        pila.append(38);
        break;
    case 28:
        pila.append(44);
        break;
    case 29:
        pila.append(45);
        break;
    case 30:
        pila.append(48);
        break;
    case 31:
        pila.append(2022);
        pila.append(22);
        pila.append(1020);
        pila.append(2007);
        pila.append(17);
        break;
    case 32:
        pila.append(18);
        pila.append(1002);
        pila.append(2006);
        break;
    case 33:
        pila.append(1043);
        break;
    case 34:
        pila.append(19);
        break;
    case 35:
        pila.append(1034);
        pila.append(20);
        pila.append(1019);
        break;
    case 36:
        pila.append(21);
        pila.append(22);
        break;
    case 37:
        pila.append(20);
        pila.append(1007);
        break;
    case 38:
        pila.append(1043);
        break;
    case 39:
        pila.append(23);
        pila.append(24);
        break;
    case 40:
        pila.append(22);
        pila.append(1033);
        break;
    case 41:
        pila.append(1043);
        break;
    case 42:
        pila.append(25);
        pila.append(26);
        break;
    case 43:
        pila.append(24);
        pila.append(1032);
        break;
    case 44:
        pila.append(1043);
        break;
    case 45:
        pila.append(28);
        pila.append(27);
        break;
    case 46:
        pila.append(1035);
        break;
    case 47:
        pila.append(1043);
        break;
    case 48:
        pila.append(29);
        pila.append(31);
        break;
    case 49:
        pila.append(1043);
        break;
    case 50:
        pila.append(31);
        pila.append(30);
        break;
    case 51:
        pila.append(1026);
        pila.append(2029);
        break;
    case 52:
        pila.append(1027);
        pila.append(2030);
        break;
    case 53:
        pila.append(1028);
        pila.append(2031);
        break;
    case 54:
        pila.append(1029);
        pila.append(2032);
        break;
    case 55:
        pila.append(1030);
        pila.append(2033);
        break;
    case 56:
        pila.append(1031);
        pila.append(2029);
        break;
    case 57:
        pila.append(32);
        pila.append(2019);
        pila.append(34);
        break;
    case 58:
        pila.append(1043);
        break;
    case 59:
        pila.append(31);
        pila.append(33);
        break;
    case 60:
        pila.append(1024);
        pila.append(2020);
        break;
    case 61:
        pila.append(1025);
        pila.append(2021);
        break;
    case 62:
        pila.append(35);
        pila.append(2015);
        pila.append(37);
        break;
    case 63:
        pila.append(1043);
        break;
    case 64:
        pila.append(34);
        pila.append(36);
        break;
    case 65:
        pila.append(1021);
        pila.append(2016);
        break;
    case 66:
        pila.append(1022);
        pila.append(2017);
        break;
    case 67:
        pila.append(1023);
        pila.append(2018);
        break;
    case 68:
        pila.append(17);
        break;
    case 69:
        pila.append(1036);
        pila.append(2008);
        break;
    case 70:
        pila.append(1037);
        pila.append(2009);
        break;
    case 71:
        pila.append(1038);
        pila.append(2010);
        break;
    case 72:
        pila.append(1039);
        pila.append(2011);
        break;
    case 73:
        pila.append(1040);
        pila.append(2012);
        break;
    case 74:
        pila.append(1042);
        pila.append(2014);
        pila.append(22);
        pila.append(1041);
        pila.append(2013);
        break;
    case 75:
        pila.append(2028);
        pila.append(1013);
        pila.append(2027);
        pila.append(39);
        pila.append(12);
        pila.append(2025);
        pila.append(1008);
        pila.append(2024);
        pila.append(22);
        pila.append(1003);
        pila.append(2023);
        break;
    case 76:
        pila.append(43);
        pila.append(40);break;
    case 77:
        pila.append(1043);break;
    case 78:
        pila.append(41);
        pila.append(42);break;
    case 79:
        pila.append(1043);
        break;
    case 80:
        pila.append(40);break;
    case 81:
        pila.append(12);
        pila.append(1008);
        pila.append(22);
        pila.append(1011);break;
    case 82:
        pila.append(12);
        pila.append(2026);
        pila.append(1008);
        pila.append(1012);
        break;
    case 83:
        pila.append(1043);
        break;
    case 84:
        pila.append(2038);
        pila.append(1010);
        pila.append(12);
        pila.append(2037);
        pila.append(1008);
        pila.append(2036);
        pila.append(22);
        pila.append(2035);
        pila.append(1004);
        break;
    case 85:
        pila.append(2040);
        pila.append(1042);
        pila.append(46);
        pila.append(1041);
        pila.append(1005);
        pila.append(2039);
        break;
    case 86:
        pila.push(47);
        pila.push(1002);
        pila.append(2006);
        break;
    case 87:
        pila.append(46);
        pila.append(1007);
        break;
    case 88:
        pila.append(1043);break;
    case 89:
        pila.append(1042);
        pila.append(49);
        pila.append(1041);
        pila.append(1006);
        pila.append(2041);
        break;
    case 90:
        pila.append(50);
        pila.append(22);break;
    case 91:
        pila.append(49);
        pila.append(1007);break;
    case 92:
        pila.append(1043);break;

    }
    return ubicacion;
}
