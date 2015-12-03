#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <mylib.h>
#include <iomanip>
using namespace std;
#define max 10000
int chon;
//////////////////////////////
////////PHAN CHUNG////////////
//////////////////////////////
//khai báo
struct ngay
{
	int ngay, thang, nam;
};
typedef ngay ngayThang;
struct book			//dang cua moi quyen sach
{
	string MASACH;
	string TUASACH;
	string tacGia;
	string viTri;
    string soTrang;
	string NXB;
	int soLanMuon;
	int trangThai;  //0: cho mượn được, 1: đã cho mượn, 2: đã bị thanh lý.
};
book sach[max];
int soLuongSach=0;
struct MUONTRA
{
	string MASACH;
	int tthai;  //0: chưa trả, 1: đã trả, 2: làm mất.
	ngayThang ngayMuon,ngayTra;
	MUONTRA *next;
};
typedef MUONTRA *MT;
struct node
{
	int MADG;
	int soSachDangMuon;
	string Ho;
	string Ten;
	string Phai;
	struct node *left;
	struct node *right;
    struct MUONTRA *CONTRO;
};
typedef node *DDG;
DDG DG;
struct dsQuaHan
{
    int madg;
    string masach;
    int thoiGianQuaHan;
    struct dsQuaHan *next;
};
typedef dsQuaHan *QH;
QH QH_First=NULL;
/////giao dien
void giaoDien_chinh()
{
	system("cls");
	system("color 2E");	//mau nen va mau chu chinh cho toan bo phan main(xy: x_mau nen, y_mau chu)
	//khung tieu de
	gotoxy(20,0); cout<<"****************************************";
	gotoxy(20,1); cout<<"*           QUAN LI THU VIEN           *";
	gotoxy(20,2); cout<<"****************************************";
	SetBGColor(7);	//mau nen thanh gioi thieu nhom
	SetColor(12);	//mau chu thanh gioi thieu nhom
	gotoxy(10,3); cout<<" Nhom: 9     Thanh Vien : Dao Trung Duyet         Le Duc Thinh   ";
	SetBGColor(8); 		// tao mau nut
	SetColor(14);		//tao mau chu
	//tao nut thu vien
	gotoxy(10,6); cout<<"   Thu Vien    ";
	//tao nut doc gia
	gotoxy(28,6); cout<<"    Doc Gia    ";
	//tao nut muon tra
	gotoxy(46,6); cout<<"   Muon Tra    ";
	//tao nut thoat
	gotoxy(64,6); cout<<"     Thoat     ";
}
void giaoDien_bangChon()
{
	int x=10, y=6;
	char nut;
	while(1)
	{
		//////////////////////
		//bang chon thu vien//
		//////////////////////
		if(x==10&&y==6)
		{
			SetBGColor(2);
			SetColor(10);
			gotoxy(10,6);
			cout<<"   Thu Vien    ";
			do
			{
				do
				{
					nut=getch();
				} while(nut!=13&&nut!=77&&nut!=75&&nut!=80); //13:enter,77:qua phai,75:qua trai,80:di xuong,72:di len.
				if(nut==13||nut==80)		//neu phim vao la enter hoac di xuong thi o do dc chon
				{
					for(int i=1;i<=8;i++) //dung for de ko can phai viet nhieu lan gotoxy
					{						// i khoi tao =1 vi neu i=0, thi se bi in ngay tren dong "thu vien"
						if(i%2==0)		//cach 2 o thi in 1 dong thong tin
						{
							SetBGColor(7);
							SetColor(5);
							gotoxy(5,y+i);
							switch(i)
							{
								case 2:
									cout<<"        Nhap sach        ";
									break;
								case 4:
									cout<<"      Thanh ly sach      ";
									break;
								case 6:
									cout<<"    Tim sach theo ten    ";
									break;
                                case 8:
                                    cout<<" 10 sach muon nhieu nhat ";
                                    break;
							}
						}
						else		//ngoai ra thi in khoang trong tao khoan cach giua cac dong thong tin
						{
							SetBGColor(4);
							gotoxy(5,y+i);
							for(int j=0;j<25;j++)
								cout<<" ";
						}
					}	//ket thuc vong for
					do
					{
						nut=getch();
					} while(nut!=77&&nut!=75&&nut!=80&&nut!=72);
					do
					{
						if(nut==80)			//neu mui ten xuong thi:
							y=y+2;		//nhay xuong 2 o(chay vao cac muc chon trong thanh vua truot xuong).
						else
							if(nut==72)		//neu mui ten len thi:
								y=y-2;	//nhay len 2 o.
							else
								break;		//neu mui ten trai hoac phai thi thoat khoi menu thu vien.
						if(y<8)			//luc nay dy dang co gia tri la 6, dung dy vi khong mun gia tri cua dy bi thay doi.
							y=14;			//lenh nay la khi dung mui ten vuot qua bang chon thi thanh chon tu nhay xuong vi tri duoi cung
						if(y>14)			//lenh nay la khi dung mui ten vuot qua bang chon phia duoi
							y=8;			//thi thanh chon tu nhay len dau hang.
						gotoxy(5,y);		//day la lenh nhay, cai' tren la gan gia tri.
						switch(y)
						{
							case 8 :
								SetBGColor(2);
								SetColor(10);
								cout<<"        Nhap sach        ";
								do
								{
									nut=getch();
									if(nut==13)
									{
										chon=1;
										return;
									}									//Neu nhan phim mten thi di tiep, enter thi chon=1,
								} while(nut!=80&&nut!=72&&nut!=77&&nut!=75); //nhan phim khac thi bat ko co hien tuong gi.
								SetBGColor(7);
								SetColor(5);
								gotoxy(5,y);
								cout<<"        Nhap sach        ";
								break;
							case 10 :
								SetBGColor(2);
								SetColor(10);
								cout<<"      Thanh ly sach      ";
								do
								{
									nut=getch();
									if(nut==13)
									{
										chon=2;
										return;
									}
								}while(nut!=80&&nut!=72&&nut!=77&&nut!=75);
								SetBGColor(7);
								SetColor(5);
								gotoxy(5,y);
								cout<<"      Thanh ly sach      ";
								break;
							case 12 :
								SetBGColor(2);
								SetColor(10);
								cout<<"    Tim sach theo ten    ";
								do
								{
									nut=getch();
									if(nut==13)
									{
										chon=3;
										return;
									}
								}while(nut!=80&&nut!=72&&nut!=77&&nut!=75);
								SetBGColor(7);
								SetColor(5);
								gotoxy(5,y);
								cout<<"    Tim sach theo ten    ";
								break;
                            case 14:
								SetBGColor(2);
								SetColor(10);
								cout<<" 10 sach muon nhieu nhat ";
								do
								{
									nut=getch();
									if(nut==13)
									{
										chon=6;
										return;
									}
								}while(nut!=80&&nut!=72&&nut!=77&&nut!=75);
								SetBGColor(7);
								SetColor(5);
								gotoxy(5,y);
								cout<<" 10 sach muon nhieu nhat ";
								break;
						}
					}while(nut!=77&&nut!=75);	// neu dung mten qua trai hoac phai thi chuyen bang chon.
                }
				if(nut==77)		//neu mten qua phai
				{
					x=28;		//nhay den vi tri cua bang "doc gia"
					y=6;
					break;		//dung break de thoat khoi bang hien tai. neu khong. chuong trinh ko nhay bang chon duoc
				}
				if(nut==75)		//neu mten qua trai
				{
					x=64;		//nhay den vi tri cua bang "thoat"
					y=6;
					break;
				}
			}while(nut!=77&&nut!=75&&nut!=80); //khi nut khac qua phai, qua trai, xuong
			SetBGColor(8);
			SetColor(14);
		    gotoxy(10,6);
		    cout<<"   Thu Vien    ";
			SetBGColor(2);
			for(int i=1;i<=8;i++)			//xoa bang khi thoat bang
			{
				gotoxy(5,y+i);
				for(int j=0;j<25;j++)
					cout<<" ";
			}
		}	//ket thuc bang "thu vien"
		/////////////////////
		//bang chon doc gia//
		/////////////////////
		if(x==28&&y==6)
		{
			SetBGColor(2);
			SetColor(10);
			gotoxy(28,6);
			cout<<"    Doc Gia    ";
			do
			{
				do
				{
					nut=getch();
				}while(nut!=13&&nut!=77&&nut!=75&&nut!=80);
				if(nut==13||nut==80)
				{
					for(int i=1;i<=8;i++)
					{
						if(i%2==0)
						{
							SetBGColor(7);
							SetColor(5);
							gotoxy(23,y+i);
							switch(i)
							{
								case 2:
									cout<<"      Nhap doc gia       ";
									break;
								case 4 :
									cout<<"       Tim doc gia       ";
									break;
								case 6:
									cout<<"      Xoa 1 doc gia      ";
									break;
								case 8 :
									cout<<" In DS DGia muon qua han ";
									break;
							}
						}
						else
						{
							SetBGColor(4);
							gotoxy(23,y+i);
							for(int j=0;j<25;j++)
								cout<<" ";
						}
					}
					do
					{
						nut=getch();
					}while(nut!=77&&nut!=75&&nut!=80&&nut!=72);
					do
					{
						if(nut==80)
							y=y+2;
						else
							if(nut==72)
								y=y-2;
						else
							break;
						if(y<8)
							y=14;
						if(y>14)
							y=8;
						gotoxy(23,y);
						switch(y)
						{
							case 8:
								SetBGColor(2);
								SetColor(10);
								cout<<"      Nhap doc gia       ";
								do
								{
									nut=getch();
									if(nut==13)
									{
										chon=7;
										return;
									}
								}while(nut!=80&&nut!=72&&nut!=77&&nut!=75);
								SetBGColor(7);
								SetColor(5);
								gotoxy(23,y);
								cout<<"      Nhap doc gia       ";
								break;
							case 10:
								SetBGColor(2);
								SetColor(10);
								cout<<"       Tim doc gia       ";
								do
								{
									nut=getch();
									if(nut==13)
									{
										chon=8;
										return;
									}
								}while(nut!=80&&nut!=72&&nut!=77&&nut!=75);
								SetBGColor(7);
								SetColor(5);
								gotoxy(23,y);
								cout<<"       Tim doc gia       ";
								break;
							case 12:
								SetBGColor(2);
								SetColor(10);
								cout<<"      Xoa 1 doc gia      ";
								do
								{
									nut=getch();
									if(nut==13)
									{
										chon=9;
										return;
									}
								}while(nut!=80&&nut!=72&&nut!=77&&nut!=75);
								SetBGColor(7);
								SetColor(5);
								gotoxy(23,y);
								cout<<"      Xoa 1 doc gia      ";
								break;
							case 14:
								SetBGColor(2);
								SetColor(10);
								cout<<" In DS DGia muon qua han ";
								do
								{
									nut=getch();
									if(nut==13)
									{
										chon=10;
										return;
									}
								}while(nut!=80&&nut!=72&&nut!=77&&nut!=75);
								SetBGColor(7);
								SetColor(5);
								gotoxy(23,y);
								cout<<" In DS DGia muon qua han ";
								break;
						}
					}while(nut!=77&&nut!=75);
				}
				if(nut==77)
				{
					x=46;	//nhay qua nut "muon tra"
					y=6;
					break;
				}
				if(nut==75)
				{
					x=10;	//nhay qua nut "thu vien"
					y=6;
					break;
				}
			}while(nut!=77&&nut!=75&&nut!=80);
			SetBGColor(8);
			SetColor(14);
			gotoxy(28,6);
			cout<<"   Doc Gia     ";
			SetBGColor(2);
			for(int i=1;i<=8;i++)			//xoa bang khi thoat bang
			{
				gotoxy(23,y+i);
				for(int j=0;j<25;j++)
					cout<<" ";
			}
		}//ket thuc bang "doc gia"
		////////////////
		///MUON TRA/////
		////////////////
		if(x==46&&y==6)
		{
			SetBGColor(2);
			SetColor(10);
			gotoxy(46,6);
			cout<<"   Muon Tra    ";
			do
			{
				do
				{
					nut=getch();
				}while(nut!=13&&nut!=77&&nut!=75&&nut!=80);
				if(nut==13||nut==80)
				{
					for(int i=1;i<=6;i++)
					{
						if(i%2==0)
						{
							SetBGColor(7);
							SetColor(5);
							gotoxy(41,y+i);
							switch(i)
							{
								case 2:
									cout<<"        Muon sach        ";
									break;
								case 4:
									cout<<"        Tra sach         ";
									break;
                                case 6:
                                    cout<<"Tim muon tra voi ten sach";
                                    break;
							}
						}
						else
						{
							SetBGColor(4);
							gotoxy(41,y+i);
							for(int j=0;j<25;j++)
								cout<<" ";
						}
					}
					do
					{
						nut=getch();
					}while(nut!=77&&nut!=75&&nut!=80&&nut!=72);
					do
					{
						if(nut==80)
							y=y+2;
						else
							if(nut==72)
								y=y-2;
							else
								break;	// thoat khoi "muon tra"
						if(y<8)
							y=12;
						if(y>12)
							y=8;
						gotoxy(41,y);
						switch(y)
						{
							case 8:
								SetBGColor(2);
								SetColor(10);
								cout<<"        Muon sach        ";
								do
								{
									nut=getch();
									if(nut==13)
										{
											chon=13;
											return;
										}
								}while(nut!=80&&nut!=72&&nut!=77&&nut!=75);
								SetBGColor(7);
								SetColor(5);
								gotoxy(41,y);
								cout<<"        Muon sach        ";
								break;
							case 10:
								SetBGColor(2);
								SetColor(10);
								cout<<"        Tra sach         ";
								do
								{
									nut=getch();
									if(nut==13)
									{
										chon=14;
										return;
									}
								}while(nut!=80&&nut!=72&&nut!=77&&nut!=75);
								SetBGColor(7);
								SetColor(5);
								gotoxy(41,y);
								cout<<"        Tra sach         ";
								break;
                            case 12:
								SetBGColor(2);
								SetColor(10);
								cout<<"Tim muon tra voi ten sach";
								do
								{
									nut=getch();
									if(nut==13)
									{
										chon=15;
										return;
									}
								}while(nut!=80&&nut!=72&&nut!=77&&nut!=75);
								SetBGColor(7);
								SetColor(5);
								gotoxy(41,y);
								cout<<"Tim muon tra voi ten sach";
								break;
						}
					}while(nut!=77&&nut!=75);
				}
				if(nut==77)
				{
					x=64;
					y=6;
					break;
				}
				if(nut==75)
				{
					x=28;
					y=6;
					break;
				}
			}while(nut!=77&&nut!=75&&nut!=80);
			SetBGColor(8);
		    SetColor(14);
			gotoxy(46,6);
			cout<<"   Muon Tra    ";
			SetBGColor(2);
			for(int i=1;i<=6;i++)			//xoa menu khi thoat bang
			{
				gotoxy(41,y+i);
				for(int j=0;j<25;j++)
				cout<<" ";
			}
		}//	ket thuc bang "muon tra"
		////////////
		///THOAT////
		////////////
		if(x==64&&y==6)
		{
			SetBGColor(2);
			SetColor(10);
			gotoxy(64,6);
			cout<<"     Thoat     ";
			do
			{
				do
				{
					nut=getch();
				}while(nut!=13&&nut!=77&&nut!=75&&nut!=80);
				if(nut==13||nut==80)
				{
					for(int i=1;i<=4;i++)
					{
						if(i%2==0)
						{
							SetBGColor(7);
							SetColor(5);
							gotoxy(59,y+i);
							switch(i)
							{
								case 2:
									cout<<"       Thoat       ";
									break;
								case 4:
									cout<<"Xoa toan bo du lieu";
									break;
							}
						}
						else
						{
							SetBGColor(4);
							gotoxy(59,y+i);
							for(int j=0;j<19;j++)
								cout<<" ";
						}
					}
					do
					{
						nut=getch();
					}while(nut!=77&&nut!=75&&nut!=80&&nut!=72);
					do
					{
						if(nut==80)
							y=y+2;
						else
							if(nut==72)
								y=y-2;
							else
								break;
						if(y<8)
							y=10;
						if(y>10)
							y=8;
						gotoxy(59,y);
						switch(y)
						{
							case 8:
								SetBGColor(2);
								SetColor(10);
								cout<<"       Thoat       ";
								do
								{
									nut=getch();
									if(nut==13)
										{
											chon=17;
											return;
										}
								}while(nut!=80&&nut!=72&&nut!=77&&nut!=75);
								SetBGColor(7);
								SetColor(5);
								gotoxy(59,y);
								cout<<"       Thoat       ";
								break;
							case 10:
								SetBGColor(2);
								SetColor(10);
								cout<<"Xoa toan bo du lieu";
								do
								{
									nut=getch();
									if(nut==13)
									{
										chon=16;
										return;
									}
								}while(nut!=80&&nut!=72&&nut!=77&&nut!=75);
								SetBGColor(7);
								SetColor(5);
								gotoxy(59,y);
								cout<<"Xoa toan bo du lieu";
								break;
						}
					}while(nut!=77&&nut!=75);
				}
				if(nut==77)
				{
					x=10;
					y=6;
					break;
				}
				if(nut==75)
				{
					x=46;
					y=6;
					break;
				}
			}while(nut!=77&&nut!=75&&nut!=80);
			SetBGColor(8);
		    SetColor(14);
			gotoxy(64,6);
			cout<<"     Thoat     ";
			SetBGColor(2);
			for(int i=1;i<=4;i++)			//xoa menu khi thoat bang
			{
				gotoxy(59,y+i);
				for(int j=0;j<19;j++)
				cout<<" ";
			}
		}
	}
}
void giaoDien_luuFile()
{
	char c;
	system("cls");
	system("color 2E");
	gotoxy(23,10); cout<<"************************************";
	gotoxy(23,11); cout<<"*        Luu File Thanh Cong!      *";
	gotoxy(23,12); cout<<"*                                  *";
	gotoxy(23,13); cout<<"* Bam ESC hoac Enter de quay lai ! *";
	gotoxy(23,14); cout<<"************************************";
	do
	{
		c=getch();		//dung getch(): nhap ko can enter, ko in ky tu ra mang hinh, nhap cac ky tu mo rong, trai lai voi scan.
	}
	while(c!=13&&c!=27);	// chi cho nhap 1 trong 2 ki tu, va chi khi nao nhap dung moi thoat dc, 13 la enter, 27 la esc
}

///////code de bam esc
void Esc()
{
	char esc;
	do					//code cho bam esc thi quay lai. ko bam dc nut khac.
    {
		esc=getch();
    }while(esc!=27);
}
/////////////////
//////SACH///////
/////////////////
//giao dien
void giaoDien_nhap_sach()
{
	int n;
	system("cls");
	system("color 2E");
	// thanh tieu de
	gotoxy(20,0); cout<<"****************************************";
	gotoxy(20,1); cout<<"*               NHAP SACH              *";
	gotoxy(20,2); cout<<"****************************************";
	gotoxy(30,3); cout<<"Bam ESC de thoat!";
	//cac thong so cua sach
	gotoxy(0,6); cout<<"Ma sach  |          Ten sach           |      Tac gia     | NXB | VT | ST  "<<endl;
	}
void giaoDien_tim_sach()
{
	system("cls");
	system("color 2E");
	gotoxy(20,0); cout<<"****************************************";
	gotoxy(20,1); cout<<"*               TIM SACH               *";
	gotoxy(20,2); cout<<"****************************************";
	gotoxy(30,3); cout<<"Bam ESC de thoat!";
}
void giaoDien_tl_sach()
{
	system("cls");
	system("color 2E");
	gotoxy(20,0); cout<<"****************************************";
	gotoxy(20,1); cout<<"*           THANH LY SACH              *";
	gotoxy(20,2); cout<<"****************************************";
	gotoxy(30,3); cout<<"Bam ESC de thoat!";
}
//////////
void doc_file_sach()
{
    string o;
	ifstream a ("SACH",ios::in);
	while(getline(a,sach[soLuongSach].MASACH)!=NULL)
	{
		getline(a,sach[soLuongSach].TUASACH);
		getline(a,sach[soLuongSach].tacGia);
		getline(a,sach[soLuongSach].NXB);
		getline(a,sach[soLuongSach].viTri);
		getline(a,sach[soLuongSach].soTrang);
        a>>sach[soLuongSach].trangThai;
        getline(a,o);
        a>>sach[soLuongSach].soLanMuon;
        getline(a,o);
        soLuongSach++;
	}
	a.close();
}
void luu_file_sach()
{
	ofstream a ("SACH",ios::out);
	for(int i=0;i<soLuongSach;i++)
		a<<sach[i].MASACH<<endl<<sach[i].TUASACH<<endl<<sach[i].tacGia<<endl<<sach[i].NXB<<endl<<sach[i].viTri<<endl<<sach[i].soTrang<<endl<<sach[i].trangThai<<endl<<sach[i].soLanMuon<<endl;
	a.close();
}
int kiemTra_maSach(int i)
{
	for(int j=0;sach[j].MASACH!="";j++)
		if(sach[j].MASACH==sach[i].MASACH&&i!=j)
			return 1;
	return 0;
}
int kiemTra_tuaSach(int i)
{
    for(int j=0;sach[j].TUASACH!="";j++)
        if(sach[j].TUASACH==sach[i].TUASACH&&i!=j)
            return 1;
    return 0;
}
void nhap_sach()
{
    system("color 2E");
    int i=soLuongSach;
    int m=soLuongSach;
    sach[i].MASACH="";
    sach[i].TUASACH="";
    sach[i].tacGia="";
    sach[i].viTri="";
    sach[i].soTrang="";
    sach[i].NXB="";
    sach[i].trangThai=0;
    sach[i].soLanMuon=0;
    int cot1=0, cot2=10, cot3=40, cot4=59, cot5=65, cot6=70;
	int x;
	char nut;
    int y=wherey();
    int co=1;
    gotoxy(cot1,y);
    while(1)
    {
        if(soLuongSach==max)
        {
            cout<<"Thu vien da day, khong the them sach!";
            do
            {
                nut=getch();
            }while(nut!=27);
            break;
        }
        else
        {
            if(co==1)			x=cot1+sach[i].MASACH.size(); //dam bao con tro luon nam o cuoi cua dong tren cot do
            else if(co==2)		x=cot2+sach[i].TUASACH.size();
            else if(co==3)		x=cot3+sach[i].tacGia.size();
            else if(co==4)		x=cot4+sach[i].NXB.size();	//4 la do dai cua nam, 4 chu so
            else if(co==5)		x=cot5+sach[i].viTri.size();
            else if(co==6)		x=cot6+sach[i].soTrang.size();
            char nut;
            do
            {
                nut=getch();
            }while(nut!=27&&nut!=13&&nut!=32&&nut!=8&&nut!=75&&nut!=77&&nut!=72&&nut!=80&&(nut<48||nut>57)&&(nut<97||nut>122));
            if(nut==27)		//ESC
            {
                break;
            }
            else if(nut==13)		//Enter
            {
                if(co==1)
                {
                    if(kiemTra_maSach(i)==1) //Kiem tra ma sach
                    {
                        SetColor(12);
                        gotoxy(10,y+2); cout<<"Ma sach da ton tai. Vui long nhap lai!";
                        gotoxy(cot1,y); cout<<sach[i].MASACH;
                        SetColor(14);
                    }
                    else if (sach[i].MASACH.size()!=6)
                    {
                        SetColor(12);
                        gotoxy(10,y+2); cout<<"Ma sach phai co 6 ky tu. Vui long nhap lai!";
                        gotoxy(cot1,y); cout<<sach[i].MASACH;
                        SetColor(14);
                    }
                    else
                    {
                        gotoxy(10,y+2); cout<<"                                            ";
                        gotoxy(cot1,y); cout<<sach[i].MASACH;
                        gotoxy(cot2-1,y); cout<<"|";
                        if(sach[i].TUASACH=="")
                        {
                            co=2;
                            gotoxy(cot3-1,y); cout<<"|";
                            gotoxy(cot2,y);
                        }
                        else if(sach[i].tacGia=="")
                        {
                            co=3;
                            gotoxy(cot4-1,y); cout<<"|";
                            gotoxy(cot3,y);
                        }
                        else if(sach[i].NXB=="")
                        {
                            co=4;
                            gotoxy(cot5-1,y); cout<<"|";
                            gotoxy(cot4,y);
                        }
                        else if(sach[i].viTri=="")
                        {
                            co=5;
                            gotoxy(cot6-1,y); cout<<"|";
                            gotoxy(cot5,y);
                        }
                        else if(sach[i].soTrang=="")
                        {
                            co=6;
                            gotoxy(cot6,y);
                        }
                        else
                        {
                            co=1;
                            gotoxy(cot1,y+1);
                            y=wherey();
                            i++;
                            soLuongSach++;
                        }
                    }
                }
                else if(co==2)
                {
                    if(sach[i].TUASACH[0]==32)
                    {
                        SetColor(12);
                        gotoxy(10,y+3); cout<<"Ban da nhap sai ten sach. Vui long nhap lai!";
                        gotoxy(cot2,y); cout<<sach[i].TUASACH;
                        SetColor(14);
                    }
                    else if(sach[i].TUASACH=="")
                    {
                        SetColor(12);
                        gotoxy(10,y+3); cout<<"Ban chua nhap ten sach. Vui long nhap!";
                        gotoxy(cot2,y); cout<<sach[i].TUASACH;
                        SetColor(14);
                    }
                    else if(kiemTra_tuaSach(i)==1)
                    {
                        SetColor(12);
                        gotoxy(10,y+3); cout<<"Sach nay da ton tai. Vui long nhap sach khac!";
                        gotoxy(cot2,y); cout<<sach[i].TUASACH;
                        SetColor(14);
                    }
                    else
                    {
                        gotoxy(10,y+3); cout<<"                                              ";  //dung de xoa dong chu thong bao in ra.
                        gotoxy(cot2,y); cout<<sach[i].TUASACH;
                        gotoxy(cot3-1,y); cout<<"|";
                        if(sach[i].MASACH=="")
                        {
                            co=1;
                            gotoxy(cot2-1,y); cout<<"|";
                            gotoxy(cot1,y);
                        }
                        else if(sach[i].tacGia=="")
                        {
                            co=3;
                            gotoxy(cot4-1,y); cout<<"|";
                            gotoxy(cot3,y);
                        }
                        else if(sach[i].NXB=="")
                        {
                            co=4;
                            gotoxy(cot5-1,y); cout<<"|";
                            gotoxy(cot4,y);
                        }
                        else if(sach[i].viTri=="")
                        {
                            co=5;
                            gotoxy(cot6-1,y); cout<<"|";
                            gotoxy(cot5,y);
                        }
                        else if(sach[i].soTrang=="")
                        {
                            co=6;
                            gotoxy(cot6,y);
                        }
                        else
                        {
                            co=1;
                            gotoxy(cot1,y+1);
                            y=wherey();
                            i++;
                            soLuongSach++;
                        }
                    }
                }
                else if(co==3)
                {
                    if(sach[i].tacGia[0]==32)
                    {
                        SetColor(12);
                        gotoxy(10,y+4); cout<<"Ban da nhap sai ten tac gia. Vui long nhap lai!";
                        gotoxy(cot3,y); cout<<sach[i].tacGia;
                        SetColor(14);
                    }
                    else if(sach[i].tacGia=="")
                    {
                        SetColor(12);
                        gotoxy(10,y+4); cout<<"Ban chua nhap ten tac gia. Vui long nhap!";
                        gotoxy(cot3,y); cout<<sach[i].tacGia;
                        SetColor(14);
                    }
                    else
                    {
                        gotoxy(10,y+4); cout<<"                                                 ";
                        gotoxy(cot3,y); cout<<sach[i].tacGia;
                        gotoxy(cot4-1,y); cout<<"|";
                        if(sach[i].MASACH=="")
                        {
                            co=1;
                            gotoxy(cot2-1,y); cout<<"|";
                            gotoxy(cot1,y);
                        }
                        else if(sach[i].TUASACH=="")
                        {
                            co=2;
                            gotoxy(cot3-1,y); cout<<"|";
                            gotoxy(cot2,y);
                        }
                        else if(sach[i].NXB=="")
                        {
                            co=4;
                            gotoxy(cot5-1,y); cout<<"|";
                            gotoxy(cot4,y);
                        }
                        else if(sach[i].viTri=="")
                        {
                            co=5;
                            gotoxy(cot6-1,y); cout<<"|";
                            gotoxy(cot5,y);
                        }
                        else if(sach[i].soTrang=="")
                        {
                            co=6;
                            gotoxy(cot6,y);
                        }
                        else
                        {
                            co=1;
                            gotoxy(cot1,y+1);
                            y=wherey();
                            i++;
                            soLuongSach++;
                        }
                    }
                }
                else if(co==4)
                {
                    if(sach[i].NXB.size()!=4)
                    {
                        SetColor(12);
                        gotoxy(10,y+5); cout<<"Ban da nhap sai nam xuat ban. Vui long nhap lai!";
                        gotoxy(cot4,y); cout<<sach[i].NXB;
                        SetColor(14);
                    }
                    else
                    {
                        gotoxy(10,y+5); cout<<"                                                 ";
                        gotoxy(cot4,y); cout<<sach[i].NXB;
                        gotoxy(cot5-1,y); cout<<"|";
                        if(sach[i].MASACH=="")
                        {
                            co=1;
                            gotoxy(cot2-1,y); cout<<"|";
                            gotoxy(cot1,y);
                        }
                        else if(sach[i].TUASACH=="")
                        {
                            co=2;
                            gotoxy(cot3-1,y); cout<<"|";
                            gotoxy(cot2,y);
                        }
                        else if(sach[i].tacGia=="")
                        {
                            co=3;
                            gotoxy(cot4-1,y); cout<<"|";
                            gotoxy(cot3,y);
                        }
                        else if(sach[i].viTri=="")
                        {
                            co=5;
                            gotoxy(cot6-1,y); cout<<"|";
                            gotoxy(cot5,y);
                        }
                        else if(sach[i].soTrang=="")
                        {
                            co=6;
                            gotoxy(cot6,y);
                        }
                        else
                        {
                            co=1;
                            gotoxy(cot1,y+1);
                            y=wherey();
                            i++;
                            soLuongSach++;
                        }
                    }
                }
                else if(co==5)
                {
                    if(sach[i].viTri.size()!=3)
                    {
                        SetColor(12);
                        gotoxy(10,y+6); cout<<"Vi tri cua sach phai co 3 ky tu. Vui long nhap lai!";
                        gotoxy(cot5,y); cout<<sach[i].viTri;
                        SetColor(14);
                    }
                    else if(sach[i].viTri[0]==32)
                    {
                        SetColor(12);
                        gotoxy(10,y+6); cout<<"Ban da nhap sai vi tri sach. Vui long nhap lai!";
                        gotoxy(cot5,y); cout<<sach[i].viTri;
                        SetColor(14);
                    }
                    else
                    {
                        gotoxy(10,y+6); cout<<"                                                   ";
                        gotoxy(cot5,y); cout<<sach[i].viTri;
                        gotoxy(cot6-1,y); cout<<"|";
                        if(sach[i].MASACH=="")
                        {
                            co=1;
                            gotoxy(cot2-1,y); cout<<"|";
                            gotoxy(cot1,y);
                        }
                        else if(sach[i].TUASACH=="")
                        {
                            co=2;
                            gotoxy(cot3-1,y); cout<<"|";
                            gotoxy(cot2,y);
                        }
                        else if(sach[i].tacGia=="")
                        {
                            co=3;
                            gotoxy(cot4-1,y); cout<<"|";
                            gotoxy(cot3,y);
                        }
                        else if(sach[i].NXB=="")
                        {
                            co=4;
                            gotoxy(cot5-1,y); cout<<"|";
                            gotoxy(cot4,y);
                        }
                        else if(sach[i].soTrang=="")
                        {
                            co=6;
                            gotoxy(cot6,y);
                        }
                        else
                        {
                            co=1;
                            gotoxy(cot1,y+1);
                            y=wherey();
                            i++;
                            soLuongSach++;
                        }
                    }
                }
                else if(co==6)
                {
                    if(sach[i].soTrang.size()>5)
                    {
                        SetColor(12);
                        gotoxy(10,y+7); cout<<"So trang sach chi co toi da 5 chu so. Vui long nhap lai!";
                        gotoxy(cot6,y); cout<<sach[i].soTrang;
                        SetColor(14);
                    }
                    else if(sach[i].soTrang.size()==0)
                    {
                        SetColor(12);
                        gotoxy(10,y+7); cout<<"Ban chua nhap so trang sach. Vui long nhap lai!";
                        gotoxy(cot6,y); cout<<sach[i].soTrang;
                        SetColor(14);
                    }
                    else
                    {
                        gotoxy(10,y+7); cout<<"                                                         ";
                        gotoxy(cot6,y); cout<<sach[i].soTrang;
                        if(sach[i].MASACH=="")
                        {
                            co=1;
                            gotoxy(cot2-1,y); cout<<"|";
                            gotoxy(cot1,y);
                        }
                        else if(sach[i].TUASACH=="")
                        {
                            co=2;
                            gotoxy(cot3-1,y); cout<<"|";
                            gotoxy(cot2,y);
                        }
                        else if(sach[i].tacGia=="")
                        {
                            co=3;
                            gotoxy(cot4-1,y); cout<<"|";
                            gotoxy(cot3,y);
                        }
                        else if(sach[i].NXB=="")
                        {
                            co=4;
                            gotoxy(cot5-1,y); cout<<"|";
                            gotoxy(cot4,y);
                        }
                        else if(sach[i].viTri=="")
                        {
                            co=5;
                            gotoxy(cot6-1,y); cout<<"|";
                            gotoxy(cot5,y);
                        }
                        else
                        {
                            co=1;
                            gotoxy(cot1,y+1);
                            y=wherey();
                            i++;
                            soLuongSach++;
                        }
                    }
                }
            }
            else if ((nut>=48&&nut<=57)||(nut>=97&&nut<=122)||(nut==32))
            {
                if(co==1&&x<9&&nut!=32) //nếu chữ chuỗi nhập vào vượt quá vị trí số 8 trên màng hình thì không cho nhập nữa.
                {
                    gotoxy(x,y);
                    if (nut>=97&&nut<=122)
                        nut=nut-32;
                    cout<<nut;  //in nút vừa nhập.
                    sach[i].MASACH.insert(sach[i].MASACH.end(),1,nut);  //chèn thêm ký tự vào cuối dãy vừa nhập.
                    x++;
                }
                else if(co==2&&x<40)
                {
                    gotoxy(x,y);
                    if (nut>=97&&nut<=122)
                        nut=nut-32;
                    cout<<nut;
                    sach[i].TUASACH.insert(sach[i].TUASACH.end(),1,nut);
                    x++;
                }
                else if(co==3&&x<59)
                {
                    gotoxy(x,y);
                    if (nut>=97&&nut<=122)
                        nut=nut-32;
                    cout<<nut;
                    sach[i].tacGia.insert(sach[i].tacGia.end(),1,nut);
                    x++;
                }
                else if(co==4&&x<65&&(nut>=48&&nut<=57))
                {
                    gotoxy(x,y);
                    cout<<nut;
                    sach[i].NXB.insert(sach[i].NXB.end(),1,nut);
                    x++;
                }
                else if(co==5&&x<70)
                {
                    gotoxy(x,y);
                    if(nut>=97&&nut<=122)
                        nut=nut-32;
                    cout<<nut;
                    sach[i].viTri.insert(sach[i].viTri.end(),1,nut);
                    x++;
                }
                else if(co==6&&x<76&&(nut>=48&&nut<=57))
                {
                    gotoxy(x,y);
                    cout<<nut;
                    sach[i].soTrang.insert(sach[i].soTrang.end(),1,nut);
                    x++;
                }
            }
            else if(nut==8)		//Backspace
            {
                if(co==1&&sach[i].MASACH!="")
                {
                    x--;
                    gotoxy(x,y);
                    cout<<" ";
                    gotoxy(x,y);
                    sach[i].MASACH.erase(sach[i].MASACH.end()-1);
                }
                else if(co==2&&sach[i].TUASACH!="")
                {
                    x--;
                    gotoxy(x,y);
                    cout<<" ";
                    gotoxy(x,y);
                    sach[i].TUASACH.erase(sach[i].TUASACH.end()-1);
                }
                else if(co==3&&sach[i].tacGia!="")
                {
                    x--;
                    gotoxy(x,y);
                    cout<<" ";
                    gotoxy(x,y);
                    sach[i].tacGia.erase(sach[i].tacGia.end()-1);
                }
                else if(co==4&&sach[i].NXB!="")
                {
                    x--;
                    gotoxy(x,y);
                    cout<<" ";
                    gotoxy(x,y);
                    sach[i].NXB.erase(sach[i].NXB.end()-1);
                }
                else if(co==5&&sach[i].viTri!="")
                {
                    x--;
                    gotoxy(x,y);
                    cout<<" ";
                    gotoxy(x,y);
                    sach[i].viTri.erase(sach[i].viTri.end()-1);
                }
                else if(co==6&&sach[i].soTrang!="")
                {
                    x--;
                    gotoxy(x,y);
                    cout<<" ";
                    gotoxy(x,y);
                    sach[i].soTrang.erase(sach[i].soTrang.end()-1);
                }
            }
            else if(nut==72)  //mui ten di len
            {
                if (i>m)
                {
                    i=i-1;  //số thứ tự sách giảm 1.
                    y=y-1;  //vị trí của con trỏ đi lên 1 hàng.
                    if(co==1)
                        gotoxy(cot1+sach[i].MASACH.size(),y);
                    else if(co==2)
                        gotoxy(cot2+sach[i].TUASACH.size(),y);
                    else if(co==3)
                        gotoxy(cot3+sach[i].tacGia.size(),y);
                    else if(co==4)
                        gotoxy(cot4+sach[i].NXB.size(),y);
                    else if(co==5)
                        gotoxy(cot5+sach[i].viTri.size(),y);
                    else if(co==6)
                        gotoxy(cot6+sach[i].soTrang.size(),y);
                }
            }
            else if (nut==80) //mui ten di xuong
            {
                i=i+1;
                y=y+1;
                if(co==1&&i<=soLuongSach)  //phải giới hạn số lượng sách để không bị vượt quá bảng nhập.
                    gotoxy(cot1+sach[i].MASACH.size(),y);
                else if(co==2&&i<=soLuongSach)
                    gotoxy(cot2+sach[i].TUASACH.size(),y);
                else if(co==3&&i<=soLuongSach)
                    gotoxy(cot3+sach[i].tacGia.size(),y);
                else if(co==4&&i<=soLuongSach)
                    gotoxy(cot4+sach[i].NXB.size(),y);
                else if(co==5&&i<=soLuongSach)
                    gotoxy(cot5+sach[i].viTri.size(),y);
                else if(co==6&&i<=soLuongSach)
                    gotoxy(cot6+sach[i].soTrang.size(),y);
                else    //cái này là để khi i>soLuongSach thì không chạy xuống được nữa.
                {
                    i--;
                    y--;
                }
            }
            else if (nut==75) //mui ten qua trai
            {
                if(co==1)
                {
                    co=6;
                    gotoxy(cot6+sach[i].soTrang.size(),y);
                }
                else if(co==2)
                {
                    co=1;
                    gotoxy(cot1+sach[i].MASACH.size(),y);
                }
                else if(co==3)
                {
                    co=2;
                    gotoxy(cot2+sach[i].TUASACH.size(),y);
                }
                else if(co==4)
                {
                    co=3;
                    gotoxy(cot3+sach[i].tacGia.size(),y);
                }
                else if(co==5)
                {
                    co=4;
                    gotoxy(cot4+sach[i].NXB.size(),y);
                }
                else if(co==6)
                {
                    co=5;
                    gotoxy(cot5+sach[i].viTri.size(),y);
                }
            }
            else if (nut==77) //mui ten qua phai
            {
                if(co==1)
                {
                    gotoxy(cot2-1,y);
                    cout<<"|";
                    co=2;
                    gotoxy(cot2+sach[i].TUASACH.size(),y);
                }
                else if(co==2)
                {
                    gotoxy(cot3-1,y);
                    cout<<"|";
                    co=3;
                    gotoxy(cot3+sach[i].tacGia.size(),y);
                }
                else if(co==3)
                {
                    gotoxy(cot4-1,y);
                    cout<<"|";
                    co=4;
                    gotoxy(cot4+sach[i].NXB.size(),y);
                }
                else if(co==4)
                {
                    gotoxy(cot5-1,y);
                    cout<<"|";
                    co=5;
                    gotoxy(cot5+sach[i].viTri.size(),y);
                }
                else if(co==5)
                {
                    gotoxy(cot6-1,y);
                    cout<<"|";
                    co=6;
                    gotoxy(cot6+sach[i].soTrang.size(),y);
                }
                else if(co==6)
                {
                    co=1;
                    gotoxy(cot1+sach[i].MASACH.size(),y);
                }
            }
        }
    }
}
void thanhLy_sach()
{
    system("color 2E");
    if(soLuongSach==0)
    {
        gotoxy(10,5);
        SetColor(14);
        cout<<"Chua co quyen sach nao trong thu vien."<<endl;
        system("Pause");
        return;
    }
	gotoxy(10,5); cout<<"Nhap ten sach thanh ly: ";
	SetBGColor(8);
	gotoxy(34,5); cout<<"                                       ";
	string s;
	int kt=0;
	char nut;
	int vt;
	while(kt==0)
	{
        vt=34+s.size();
        do
        {
            fflush(stdin);
            nut=getch();
        }while(nut!=27&&nut!=13&&nut!=8&&nut!=32&&(nut<48||nut>57)&&(nut<97||nut>122)&&(nut>65||nut<90));
        if (nut==27)			//ESC
        {
            kt=1;
            break;
        }
        else if (nut==13)			//Enter
        {
            gotoxy(34,5); cout<<s;
            int i;
            for(i=0; i<soLuongSach; i++)     //Chạy từ 0 đến hết danh sách của sách
                if(sach[i].TUASACH==s) break;    //nếu tìm thấy tên trùng thì thoát vòng for.
            if(i==soLuongSach)
            {
                SetColor(7);
                gotoxy(20,7); cout<<"Sach sai hoac khong ton tai. Vui long kiem tra lai!";
                gotoxy(34,5); cout<<s;
            }
            else
            {
                sach[i].trangThai=2;
                SetBGColor(2);
                gotoxy(20,7); cout<<"                                                   ";
                SetColor(7);
                SetBGColor(2);
                gotoxy(20,7); cout<<"Thanh ly thanh cong. Vui long nhan Esc de quay lai! ";
                Esc();
                return;
            }
        }
        else if ((nut>=48&&nut<=57)||(nut>=97&&nut<=122)||(nut>=65&&nut<=90)||nut==32)
        {
                gotoxy(vt,5);
                if(nut>=97&&nut<=122)
                    nut=nut-32;		//In chu hoa
                cout<<nut;
                s.insert(s.end(),1,nut);
                vt++;
        }
        else if (nut==8)
        {
            if (s.size()!=0)
            {
                vt--;
                gotoxy(vt,5);
                cout <<" ";
                gotoxy(vt,5);
                s.erase(s.end()-1);
            }
        }
    }
}
void delete_tb_sach()
{
    ofstream a ("SACH",ios::trunc);
    a.close();
}
////////////////////
/////DOC GIA////////
////////////////////
//khai bao
////////giao dien
void giaoDien_nhap_docGia()
{
	system("cls");
	system("color 2E");
	gotoxy(20,0); cout<<"****************************************";
	gotoxy(20,1); cout<<"*             NHAP DOC GIA             *";
	gotoxy(20,2); cout<<"****************************************";
	gotoxy(30,3); cout<<"Bam ESC de thoat!";
	gotoxy(0,6);  cout<<" Ma doc gia |       Ho       |            Ten          | Gioi tinh |"<<endl;
}
void giaoDien_tim_docGia()
{
	system("cls");
	system("color 2E");
	gotoxy(20,0); cout<<"****************************************";
	gotoxy(20,1); cout<<"*              TIM DOC GIA             *";
	gotoxy(20,2); cout<<"****************************************";
	gotoxy(30,3); cout<<"Bam ESC de thoat!";
}
void giaoDien_xoa_docGia()
{
	system("cls");
	system("color 2E");
	gotoxy(20,0); cout<<"****************************************";
	gotoxy(20,1); cout<<"*              XOA DOC GIA             *";
	gotoxy(20,2); cout<<"****************************************";
	gotoxy(30,3); cout<<"Bam ESC de thoat!";
	gotoxy(10,5); cout<<"Nhap ma doc gia can xoa: ";
	SetBGColor(8);
	gotoxy(38,5);
	cout<<"                              ";
}
/////////////
DDG last;
void Insert_node(DDG &a,node x)
{
    if(a==NULL)
    {
        a=new node;
        a->MADG=x.MADG;
        a->Ho=x.Ho;
        a->Ten=x.Ten;
        a->Phai=x.Phai;
        a->left=NULL;
        a->right=NULL;
        a->CONTRO=NULL;
        a->soSachDangMuon=x.soSachDangMuon;
        last=a;
    }
    else if(x.MADG<a->MADG)     Insert_node(a->left,x);
    else if(x.MADG>a->MADG)     Insert_node(a->right,x);
}
DDG search_dg(int x)
{
    DDG p;
    p=DG;
    while(p!=NULL &&p->MADG!=x)
        if(x<p->MADG)    p=p->left;
        else            p=p->right;
    return (p);
}
int kiemTra_madg(string x)
{
    DDG p;
    int madg;
    madg=atoi(x.c_str());
    p=search_dg(madg);
    if(p==NULL) return 0;
    else    return 1;
}
void nhap_dg()
{
    node a;
    system("color 2E");
    int madg=0;
    string ma="";
    string h="";
    string t="";
    string p="";
    a.soSachDangMuon=0;
    int cot1=0, cot2=13, cot3=30, cot4=56, cot5=68;
	int x;
    int y=wherey();
    DDG b;
    int co=1;
    char nut;
    gotoxy(cot1,y);
    while(1)
    {
        if(co==1)       x=cot1+ma.size();
        else if(co==2)  x=cot2+h.size();
        else if(co==3)  x=cot3+t.size();
        else if(co==4)  x=cot4+p.size();
        do
        {
            nut=getch();
        }while(nut!=27&&nut!=13&&nut!=32&&nut!=8&&nut!=75&&nut!=77&&nut!=72&&nut!=80&&(nut<48||nut>57)&&(nut<97||nut>122));
        if(nut==27)
        {
            break;
        }
        else if(nut==32||(nut>=48&&nut<=57)||(nut>=97&&nut<=122))
        {
            if(co==1&&x<12&&(nut>=48&&nut<=57))
            {
                gotoxy(x,y);
                cout<<nut;
                ma.insert(ma.end(),1,nut);
                x++;
            }
            else if(co==2&&x<29)
            {
                gotoxy(x,y);
                if(nut>=97&&nut<=122)
                    nut=nut-32;
                cout<<nut;
                h.insert(h.end(),1,nut);
                x++;
            }
            else if(co==3&&x<55)
            {
                gotoxy(x,y);
                if(nut>=97&&nut<=122)
                    nut=nut-32;
                cout<<nut;
                t.insert(t.end(),1,nut);
                x++;
            }
            else if(co==4&&x<60)
            {
                gotoxy(x,y);
                nut=nut-32;
                cout<<nut;
                p.insert(p.end(),1,nut);
                x++;
            }
        }
        else if(nut==8)
        {
            if(co==1&&ma!="")
            {
                x--;
                gotoxy(x,y);
                cout<<" ";
                gotoxy(x,y);
                ma.erase(ma.end()-1);
            }
            else if(co==2&&h!="")
            {
                x--;
                gotoxy(x,y);
                cout<<" ";
                gotoxy(x,y);
                h.erase(h.end()-1);
            }
            else if(co==3&&t!="")
            {
                x--;
                gotoxy(x,y);
                cout<<" ";
                gotoxy(x,y);
                t.erase(t.end()-1);
            }
            else if(co==4&&p!="")
            {
                x--;
                gotoxy(x,y);
                cout<<" ";
                gotoxy(x,y);
                p.erase(p.end()-1);
            }
        }
        else if (nut==75) //mui ten qua trai
        {
            if(co==1)
            {
                co=4;
                gotoxy(cot4+p.size(),y);
            }
            else if(co==2)
            {
                co=1;
                gotoxy(cot1+ma.size(),y);
            }
            else if(co==3)
            {
                co=2;
                gotoxy(cot2+h.size(),y);
            }
            else if(co==4)
            {
                co=3;
                gotoxy(cot3+t.size(),y);
            }
        }
        else if (nut==77) //mui ten qua phai
        {
            if(co==1)
            {
                gotoxy(cot2-1,y);
                cout<<"|";
                co=2;
                gotoxy(cot2+h.size(),y);
            }
            else if(co==2)
            {
                gotoxy(cot3-1,y);
                cout<<"|";
                co=3;
                gotoxy(cot3+t.size(),y);
            }
            else if(co==3)
            {
                gotoxy(cot4-1,y);
                cout<<"|";
                co=4;
                gotoxy(cot4+p.size(),y);
            }
            else if(co==4)
            {
                gotoxy(cot1-1,y);
                co=1;
                gotoxy(cot1+ma.size(),y);
            }
        }
        else if(nut==13)
        {
            if(co==1)
            {
                if(ma.size()!=5)
                {
                    SetColor(12);
                    gotoxy(10,y+2); cout<<"Ma doc gia chi phai co 5 ky tu. Vui long nhap lai!";
                    gotoxy(cot1,y); cout<<ma;
                    SetColor(14);
                }
                else if(ma=="")
                {
                    SetColor(12);
                    gotoxy(10,y+2); cout<<"Ban chua nhap ma doc gia. Vui long nhap!          ";
                    gotoxy(cot1,y); cout<<ma;
                    SetColor(14);
                }
                else if(kiemTra_madg(ma)==1)
                {
                    SetColor(12);
                    gotoxy(10,y+2); cout<<"Ma doc gia da bi trung. Vui long nhap lai!        ";
                    gotoxy(cot1,y); cout<<ma;
                    SetColor(14);
                }
                else
                {
                    gotoxy(10,y+2); cout<<"                                                  ";
                    gotoxy(cot1,y); cout<<ma;
                    madg=atoi(ma.c_str());
                    gotoxy(cot2-1,y); cout<<"|";
                    if(h=="")
                    {
                        co=2;
                        gotoxy(cot3-1,y); cout<<"|";
                        gotoxy(cot2,y);
                    }
                    else if(t=="")
                    {
                        co=3;
                        gotoxy(cot4-1,y); cout<<"|";
                        gotoxy(cot3,y);
                    }
                    else if(p=="")
                    {
                        co=4;
                        gotoxy(cot5-1,y); cout<<"|";
                        gotoxy(cot4,y);
                    }
                    else
                    {
                        gotoxy(cot2-1,y); cout<<"|";
                        co=1;
                        gotoxy(cot1,y+1);
                        y=wherey();
                        a.MADG=madg;
                        a.Ho=h;
                        a.Ten=t;
                        a.Phai=p;
                        Insert_node(DG,a);
                        break;
                    }
                }
            }
            else if(co==2)
            {
                if(h[0]==32)
                {
                    SetColor(12);
                    gotoxy(10,y+3); cout<<"Ban da nhap sai ho. Vui long nhap lai!";
                    gotoxy(cot2,y); cout<<h;
                    SetColor(14);
                }
                else if(h=="")
                {
                    SetColor(12);
                    gotoxy(10,y+3); cout<<"Ban chua nhap ho doc gia. Vui long nhap!";
                    gotoxy(cot2,y); cout<<h;
                    SetColor(14);
                }
                else
                {
                    gotoxy(10,y+3); cout<<"                                                ";
                    gotoxy(cot2,y); cout<<h;
                    gotoxy(cot3-1,y); cout<<"|";
                    if(ma=="")
                    {
                        co=1;
                        gotoxy(cot2-1,y); cout<<"|";
                        gotoxy(cot1,y);
                    }
                    else if(t=="")
                    {
                        co=3;
                        gotoxy(cot4-1,y); cout<<"|";
                        gotoxy(cot3,y);
                    }
                    else if(p=="")
                    {
                        co=4;
                        gotoxy(cot5-1,y); cout<<"|";
                        gotoxy(cot4,y);
                    }
                    else
                    {
                        co=1;
                        gotoxy(cot3-1,y); cout<<"|";
                        gotoxy(cot1,y+1);
                        y=wherey();
                        a.MADG=madg;
                        a.Ho=h;
                        a.Ten=t;
                        a.Phai=p;
                        Insert_node(DG,a);
                        break;
                    }
                }
            }
            else if(co==3)
            {
                if(t[0]==32)
                {
                    SetColor(12);
                    gotoxy(10,y+4); cout<<"Ban da nhap sai ten. Vui long nhap lai!";
                    gotoxy(cot3,y); cout<<t;
                    SetColor(14);
                }
                else if(t=="")
                {
                    SetColor(12);
                    gotoxy(10,y+4); cout<<"Ban chua nhap ten doc gia. Vui long nhap!";
                    gotoxy(cot3,y); cout<<t;
                    SetColor(14);
                }
                else
                {
                    gotoxy(10,y+4); cout<<"                                                 ";
                    gotoxy(cot3,y); cout<<t;
                    gotoxy(cot4-1,y); cout<<"|";
                    if(ma=="")
                    {
                        co=1;
                        gotoxy(cot2-1,y); cout<<"|";
                        gotoxy(cot1,y);
                    }
                    else if(h=="")
                    {
                        co=2;
                        gotoxy(cot3-1,y); cout<<"|";
                        gotoxy(cot2,y);
                    }
                    else if(p=="")
                    {
                        co=4;
                        gotoxy(cot5-1,y); cout<<"|";
                        gotoxy(cot4,y);
                    }
                    else
                    {
                        co=1;
                        gotoxy(cot4-1,y); cout<<"|";
                        gotoxy(cot1,y+1);
                        y=wherey();
                        a.MADG=madg;
                        a.Ho=h;
                        a.Ten=t;
                        a.Phai=p;
                        Insert_node(DG,a);
                        break;
                    }
                }
            }
            else if(co==4)
            {
                if(p[0]==32)
                {
                    SetColor(12);
                    gotoxy(10,y+5); cout<<"Ban da nhap sai gioi tinh. Vui long nhap lai!";
                    gotoxy(cot4,y); cout<<p;
                    SetColor(14);
                }
                else if(p=="")
                {
                    SetColor(12);
                    gotoxy(10,y+5); cout<<"Ban chua nhap gioi tinh doc gia. Vui long nhap!";
                    gotoxy(cot4,y); cout<<p;
                    SetColor(14);
                }
                else if(p!="NU"&&p!="NAM")
                {
                    SetColor(12);
                    gotoxy(10,y+5); cout<<"Gioi tinh chi co the la NAM hoac NU! Vui long nhap lai!";
                    gotoxy(cot4,y); cout<<p;
                    SetColor(14);
                }
                else
                {
                    gotoxy(10,y+5); cout<<"                                                        ";
                    gotoxy(cot4,y); cout<<p;
                    gotoxy(cot5-1,y); cout<<"|";
                    if(ma=="")
                    {
                        co=1;
                        gotoxy(cot2-1,y); cout<<"|";
                        gotoxy(cot1,y);
                    }
                    else if(h=="")
                    {
                        co=2;
                        gotoxy(cot3-1,y); cout<<"|";
                        gotoxy(cot2,y);
                    }
                    else if(t=="")
                    {
                        co=3;
                        gotoxy(cot4-1,y); cout<<"|";
                        gotoxy(cot3,y);
                    }
                    else
                    {
                        gotoxy(cot5-1,y); cout<<"|";
                        co=1;
                        gotoxy(cot1,y+1);
                        y=wherey();
                        a.MADG=madg;
                        a.Ho=h;
                        a.Ten=t;
                        a.Phai=p;
                        Insert_node(DG,a);
                        break;
                    }
                }
            }
        }
    }
}
void luu_file_dg()
{
    ofstream a ("DG",ios::out);
	DDG Stack[max];
	int sp=-1;
	while(DG!=NULL)
    {
		a<<"dg"<<endl<<DG->MADG<<"|"<<DG->Ho<<"|"<<DG->Ten<<"|"<<DG->Phai<<"|"<<DG->soSachDangMuon<<"|"<<endl;
		{
		    MUONTRA *s;
		    for(s=DG->CONTRO;s!=NULL;s=s->next)
            {
                a<<"sdm"<<endl<<s->MASACH<<endl<<s->ngayMuon.ngay<<"/"<<s->ngayMuon.thang<<"/"<<s->ngayMuon.nam<<"/"<<endl<<s->ngayTra.ngay<<"/"<<s->ngayTra.thang<<"/"<<s->ngayTra.nam<<"/"<<endl<<s->tthai<<endl;
            }
		}
		if(DG->right!=NULL)
			Stack[++sp]=DG->right;
		if(DG->left!=NULL)
			DG=DG->left;
		else if(sp==-1)
                break;
            else DG=Stack[sp--];
	}
	a.close();
}
void themMuonTra(MT &First, MUONTRA x )
{
    MT p;
    p=new MUONTRA;
    p->MASACH=x.MASACH;
    p->tthai=x.tthai;
    p->ngayMuon=x.ngayMuon;
    p->ngayTra=x.ngayTra;
    p->next = First;
    First=p;
}
void doc_file_dg()//doc file zo mang a
{
	ifstream a("DG", ios::in);
	string ma;
	string chuoi;
	string madg;
	string xdong;
	string ssach;
	node x;
	MUONTRA k;
    string ngay,thang,nam;
	while(getline(a,ma)!=NULL)
    {

    	 if(ma=="dg")
        {
            getline(a,chuoi);
            int dau=0, cuoi=0;
            cuoi=chuoi.find("|",dau);
            madg=chuoi.substr(dau,cuoi-dau);
            x.MADG=atoi(madg.c_str());
            dau=cuoi+1;
            cuoi=chuoi.find("|",dau);
            x.Ho=chuoi.substr(dau,cuoi-dau);
            dau=cuoi+1;
            cuoi=chuoi.find("|",dau);
            x.Ten=chuoi.substr(dau,cuoi-dau);
            dau=cuoi+1;
            cuoi=chuoi.find("|",dau);
            x.Phai=chuoi.substr(dau,cuoi-dau);
            dau=cuoi+1;
            cuoi=chuoi.find("|",dau);
            ssach=chuoi.substr(dau,cuoi-dau);
            x.soSachDangMuon=atoi(ssach.c_str());
            Insert_node(DG,x);
        }
        else if(ma=="sdm")
         {
            int dau=0,cuoi=0;
            getline(a,k.MASACH);
            getline(a,chuoi);
            cuoi=chuoi.find("/",dau);
            ngay=chuoi.substr(dau,cuoi-dau);
            k.ngayMuon.ngay=atoi(ngay.c_str());
            dau=cuoi+1;
            cuoi=chuoi.find("/",dau);
            thang=chuoi.substr(dau,cuoi-dau);
            k.ngayMuon.thang=atoi(thang.c_str());
            dau=cuoi+1;
            cuoi=chuoi.find("/",dau);
            nam=chuoi.substr(dau,cuoi-dau);
            k.ngayMuon.nam=atoi(nam.c_str());
            getline(a,chuoi);
            dau=0;
            cuoi=chuoi.find("/",dau);
            ngay=chuoi.substr(dau,cuoi-dau);
            k.ngayTra.ngay=atoi(ngay.c_str());
            dau=cuoi+1;
            cuoi=chuoi.find("/",dau);
            thang=chuoi.substr(dau,cuoi-dau);
            k.ngayTra.thang=atoi(thang.c_str());
            dau=cuoi+1;
            cuoi=chuoi.find("/",dau);
            nam=chuoi.substr(dau,cuoi-dau);
            k.ngayTra.nam=atoi(nam.c_str());
            a>>k.tthai;
            getline(a,xdong);
            themMuonTra(last->CONTRO,k);
         }
	}
	a.close();
}
void tim_dg()
{
    DDG p;
    system("color 2E");
    if(DG==NULL)
    {
        gotoxy(10,5);
        SetColor(12);
        cout<<"Chua co doc gia nao trong thu vien."<<endl;
        system("Pause");
        return;
    }
	gotoxy(10,5); cout<<"Nhap ma doc gia can tim: ";
	SetBGColor(8);
	gotoxy(38,5); cout<<"          ";
	string s;
	int y=wherey();
	int kt=0;
	int madg;
	char nut;
	int vt;
    while(1)
    {
        vt=40+s.size();
        do
        {
            nut=getch();
        }while(nut!=13&&nut!=27&&nut!=8&&nut!=32&&(nut<48||nut>57)&&(nut<97||nut>122)&&(nut>65||nut<90));
        if(nut==27)
        {
            break;
        }
        else if((nut>=48&&nut<=57)||(nut>=97&&nut<=122)||(nut>=65&&nut<=90)||nut==32)
        {
            gotoxy(vt,5);
                if(nut>=97&&nut<=122)
                    nut=nut-32;		//In chu hoa
                cout<<nut;
                s.insert(s.end(),1,nut);
                vt++;
        }
        else if (nut==8)
        {
            if (s.size()!=0)
            {
                vt--;
                gotoxy(vt,5);
                cout <<" ";
                gotoxy(vt,5);
                s.erase(s.end()-1);
            }
        }
        if(nut==13)
        {
            gotoxy(40,5); cout<<s;
            madg=atoi(s.c_str());
            p=search_dg(madg);
            if(p==NULL)
            {
                SetColor(12);
                gotoxy(20,7); cout<<"Ma doc gia sai hoac khong ton tai. Vui long kiem tra lai!";
                gotoxy(40,5); cout<<s;
                SetColor(14);
            }
            else if(s.size()!=5)
            {
                SetColor(12);
                gotoxy(20,7); cout<<"Ma doc gia phai co 5 ky tu. Vui long nhap lai!";
                gotoxy(40,5); cout<<s;
                SetColor(14);
            }
            else
            {
                SetBGColor(2);
                gotoxy(20,7); cout<<"                                                         ";
                gotoxy(0,8); cout<<"Ma doc gia  |      Ho      |            Ten           |    Gioi tinh   |";
                gotoxy(0,9); cout<<setw(12)<<p->MADG<<"|"<<setw(14)<<p->Ho<<"|"<<setw(26)<<p->Ten<<"|"<<setw(16)<<p->Phai<<"|";
                gotoxy(0,10); cout<<" STT |   Ma sach  |           Ten sach           |       Tac gia    |";
                gotoxy(20,11); cout<<"Cac quyen sach dang muon:"<<endl;
                int dem=0;
                for(MUONTRA *i=p->CONTRO;i!=NULL;i=i->next)
                {
                    dem++;
                    if(i->tthai==0||i->tthai==2)
                    {
                        int j;
                        for(j=0;j<soLuongSach;j++)
                            if(sach[j].MASACH==i->MASACH) break;
                        gotoxy(0,11+dem); cout<<setw(5)<<dem<<"|"<<setw(12)<<sach[j].MASACH<<"|"<<setw(30)<<sach[j].TUASACH<<"|"<<setw(18)<<sach[j].tacGia<<"|";
                    }
                }
                gotoxy(20,12+dem); cout<<"Cac quyen sach da muon: ";
                int dem2=0;
                for(MUONTRA *i=p->CONTRO;i!=NULL;i=i->next)
                {
                    dem2++;
                    if(i->tthai==1)
                    {
                        int j;
                        for(j=0;j<soLuongSach;j++)
                            if(sach[j].MASACH==i->MASACH) break;
                        gotoxy(0,12+dem+dem2); cout<<setw(5)<<dem2<<"|"<<setw(12)<<sach[j].MASACH<<"|"<<setw(30)<<sach[j].TUASACH<<"|"<<setw(18)<<sach[j].tacGia<<"|";
                    }
                }
                Esc();
                break;
            }
        }
    }
}
DDG rp;
void xoa_dg1(DDG &r)
{
    if(r->left!=NULL)
        xoa_dg1(r->left);
    else
    {
        rp->MADG=r->MADG;
        rp->Ho=r->Ho;
        rp->Ten=r->Ten;
        rp->Phai=r->Phai;
        rp=r;
        r=r->right;
    }
}
void xoa_dg2(DDG &p,int x)
{
    if(x<p->MADG)   xoa_dg2(p->left,x);
    else if(x>p->MADG)  xoa_dg2(p->right,x);
    else
    {
        rp=p;
        if(rp->right==NULL) p=rp->left;
        if(rp->left==NULL)  p=rp->right;
        else xoa_dg1(rp->right);
        free(rp);
    }
}
void xoa_dg(DDG &p)
{
    system("color 2E");
    if(p==NULL)
    {
        gotoxy(10,5);
        SetColor(14);
        cout<<"Chua co doc gia nao trong thu vien."<<endl;
        system("Pause");
        return;
    }
	gotoxy(10,5); cout<<"Nhap ma doc gia can xoa: ";
	SetBGColor(8);
	gotoxy(38,5); cout<<"                                       ";
	string s;
	int kt=0;
	char nut;
	int vt;
	while(1)
	{
        vt=38+s.size();
        do
        {
            fflush(stdin);
            nut=getch();
        }while(nut!=27&&nut!=13&&nut!=8&&nut!=32&&(nut<48||nut>57)&&(nut<97||nut>122)&&(nut>65||nut<90));
        if (nut==27)			//ESC
        {
            break;
        }
        else if (nut==13)			//Enter
        {
            if(kiemTra_madg(s)==0)
            {
                SetColor(12);
                gotoxy(20,8); cout<<"Khong tim thay ma doc gia. Vui long nhap lai!";
                gotoxy(38,5); cout<<s;
            }
            else
            {
                int madg=atoi(s.c_str());
                DDG dg;
                dg=search_dg(madg);
                MUONTRA *dsb;
                int i;
                for(dsb=dg->CONTRO;dsb!=NULL;dsb=dsb->next) //dựa vào mã sách trong danh sách sách đang mượn
                    if(dsb->tthai==0)                          //tìm xem sách nào đang mượn thì
                    {
                        dsb->tthai=1;
                        for(i=0;i<soLuongSach;i++)
                            if(sach[i].MASACH==dsb->MASACH)
                                sach[i].trangThai=0;        //trả trạng thái sách đó về 0.
                    }
                xoa_dg2(DG,madg);
                SetColor(7);
                SetBGColor(2);
                gotoxy(20,7); cout<<"Xoa thanh cong!";
            }
        }
        else if ((nut>=48&&nut<=57)||(nut>=97&&nut<=122)||(nut>=65&&nut<=90)||nut==32)
        {
                gotoxy(vt,5);
                if(nut>=97&&nut<=122)
                    nut=nut-32;		//In chu hoa
                cout<<nut;
                s.insert(s.end(),1,nut);
                vt++;
        }
        else if (nut==8)
        {
            if (s.size()!=0)
            {
                vt--;
                gotoxy(vt,5);
                cout <<" ";
                gotoxy(vt,5);
                s.erase(s.end()-1);
            }
        }
    }
}
void delete_tb_dg() //dùng để xóa file đọc giả
{
    ofstream a ("DG",ios::trunc);
    a.close();
}
void clearlist(MT &First)   //dùng để xóa danh sách mượn trả.
{
    MT p;
    while(First!=NULL)
    {
        p=First;
        First=First->next;
        free(p);
    }
}
void clearlist_tree_LRN(DDG &p) //dùng để xóa danh sách đọc giả. (dùng đệ qui)
{
    if(p!=NULL)
    {
        clearlist_tree_LRN(p->left);
        clearlist_tree_LRN(p->right);
        clearlist(p->CONTRO);
        free(p);
    }
}
//////////////
////MUON TRA//
//////////////
void LayNgayHT(int &x,int &y,int &z)//lay ngay cua he thong.
{
    int ngay,thang,nam,SoNgay ;
    tm *today ;
    time_t ltime;
    time( &ltime );
    today = localtime( &ltime );
    x=today->tm_mday;
    y=today->tm_mon+1;
    z=today->tm_year+1900;
}
ngay congNgayThang(ngay ngMuon,int soNgMuon)
{
    ngay ngTra;
    ngTra.ngay=ngMuon.ngay+soNgMuon;
    ngTra.thang=ngMuon.thang;
    ngTra.nam=ngMuon.nam;
    if(ngTra.nam%4==0)
    {
        if(ngTra.thang==2)
        {
            if(ngTra.ngay>29)
            {
                ngTra.ngay=ngTra.ngay-29;
                ngTra.thang++;
                return ngTra;
            }
            else return ngTra;
        }
        else if(ngTra.thang==1||ngTra.thang==3||ngTra.thang==5||ngTra.thang==7||ngTra.thang==8||ngTra.thang==10)
        {
            if(ngTra.ngay>31)
            {
                ngTra.ngay=ngTra.ngay-31;
                ngTra.thang++;
                return ngTra;
            }
            else return ngTra;
        }
        else if(ngTra.thang==4||ngTra.thang==6||ngTra.thang==9||ngTra.thang==11)
        {
            if(ngTra.ngay>30)
            {
                ngTra.ngay=ngTra.ngay-30;
                ngTra.thang++;
                return ngTra;
            }
            else return ngTra;
        }
        else if(ngTra.thang==12)
        {
            if(ngTra.ngay>31)
            {
                ngTra.ngay=ngTra.ngay-31;
                ngTra.thang=1;
                ngTra.nam++;
                return ngTra;
            }
            else return ngTra;
        }
    }
    else
    {
        if(ngTra.thang==2)
        {
            if(ngTra.ngay>28)
            {
                ngTra.ngay=ngTra.ngay-28;
                ngTra.thang++;
                return ngTra;
            }
            else return ngTra;
        }
        else if(ngTra.thang==1||ngTra.thang==3||ngTra.thang==5||ngTra.thang==7||ngTra.thang==8||ngTra.thang==10)
        {
            if(ngTra.ngay>31)
            {
                ngTra.ngay=ngTra.ngay-31;
                ngTra.thang++;
                return ngTra;
            }
            else return ngTra;
        }
        else if(ngTra.thang==4||ngTra.thang==6||ngTra.thang==9||ngTra.thang==11)
        {
            if(ngTra.ngay>30)
            {
                ngTra.ngay=ngTra.ngay-30;
                ngTra.thang++;
                return ngTra;
            }
            else return ngTra;
        }
        else if(ngTra.thang==12)
        {
            if(ngTra.ngay>31)
            {
                ngTra.ngay=ngTra.ngay-31;
                ngTra.thang=1;
                ngTra.nam++;
                return ngTra;
            }
            else return ngTra;
        }
    }
}
int soSanh_ngayTra_Today(ngay ngayTra, ngay Today)  //nếu như quá hạn rồi thì return 1, nếu chưa thì return 0.
{
    if(ngayTra.nam>Today.nam)
        return 0;
    else if(ngayTra.nam<Today.nam)
        return 1;
    else
        if(ngayTra.thang>Today.thang)
            return 0;
        else if(ngayTra.thang<Today.thang)
            return 1;
        else
            if(ngayTra.ngay>Today.ngay)
                return 0;
            else return 1;
}
int search_sach_muonQuaHan(int madg)        //Dùng để kiểm tra xem đọc giả có sách nào mượn quá hạn ko.
{
    ngay Today;
    LayNgayHT(Today.ngay,Today.thang,Today.nam);
    DDG dg;
    dg=search_dg(madg);
    MT mt;
    for(mt=dg->CONTRO;mt!=NULL;mt=mt->next)
        if(mt->tthai==0)
            if(soSanh_ngayTra_Today(mt->ngayTra,Today)==0)
                return 1;
    return 0;
}
void muon()
{
    MUONTRA mt;
    DDG p;
    p=DG;
    system("cls");
	system("color 2E");
	gotoxy(20,0); cout<<"****************************************";
	gotoxy(20,1); cout<<"*               MUON SACH              *";
	gotoxy(20,2); cout<<"****************************************";
	gotoxy(30,3); cout<<"Bam ESC de thoat!"<<endl;
	if(soLuongSach==0)
    {
        SetColor(12);
        cout<<"Trong thu vien chua co sach!"<<endl;
        system("Pause");
        return;
    }
    if(DG==NULL)
    {
        SetColor(12);
        cout<<"Trong thu vien chua cho doc gia!"<<endl;
        system("Pause");
        return;
    }
	gotoxy(10,5); cout<<"Ma doc gia:";
	gotoxy(40,5); cout<<"Ma sach:";
	SetBGColor(8);
	gotoxy(22,5); cout<<"          ";
	gotoxy(49,5); cout<<"          ";
    string dg="";
    string masach="";
	int madg;
	char nut;
	int vt;
	int co=1;
	gotoxy(24,5);
    while(1)
    {
        if(co==1)           vt=24+dg.size();
        else                vt=51+masach.size();
        do
        {
            nut=getch();
        }while(nut!=13&&nut!=27&&nut!=8&&(nut<48||nut>57)&&(nut<97||nut>122)&&nut!=75&&nut!=77);
        if(nut==27)
        {
            break;
        }
        else if((nut>=48&&nut<=57)||(nut>=97&&nut<=122))
        {
            SetBGColor(8);
            if(co==1&&vt<32&&(nut>=48&&nut<=57))
            {
                gotoxy(vt,5);
                cout<<nut;
                dg.insert(dg.end(),1,nut);
                vt++;
            }
            else if(co==2&&vt<59)
            {
                gotoxy(vt,5);
                if(nut>=97&&nut<=122)
                    nut=nut-32;
                cout<<nut;
                masach.insert(masach.end(),1,nut);
                vt++;
            }
        }
        else if (nut==8)
        {
            if(co==1&&dg.size()!=0)
            {
                vt--;
                gotoxy(vt,5);
                cout<<" ";
                gotoxy(vt,5);
                dg.erase(dg.end()-1);
            }
            else if(co==2&&masach.size()!=0)
            {
                vt--;
                gotoxy(vt,5);
                cout<<" ";
                gotoxy(vt,5);
                masach.erase(masach.end()-1);
            }
        }
        else if(nut==75||nut==77)
        {
            if(co==1)
            {
                co=2;
                gotoxy(51+masach.size(),5);
            }
            else if(co==2)
            {
                co=1;
                gotoxy(24+dg.size(),5);
            }
        }
        else if(nut==13)
        {
            if(co==1)
            {
                madg=atoi(dg.c_str());
                p=search_dg(madg);
                SetBGColor(2);
                if(search_sach_muonQuaHan(madg)==1)
                {
                    SetColor(12);
                    gotoxy(10,8); cout<<"Ban muon sach da qua han. Vui long tra truoc khi muon them!";
                    gotoxy(24,5); cout<<dg;
                    SetColor(14);
                }
                else if(kiemTra_madg(dg)==0)
                {
                    SetColor(12);
                    gotoxy(10,8); cout<<"Ma doc gia sai hoac khong ton tai. Vui long nhap lai!      ";
                    gotoxy(24,5); cout<<dg;
                    SetColor(14);
                }
                else if (dg.size()!=5)
                {
                    SetColor(12);
                    gotoxy(10,8); cout<<"Ma doc gia phai co 5 ky tu. Vui long nhap lai!             ";
                    gotoxy(24,5); cout<<dg;
                    SetColor(14);
                }
                else if(dg=="")
                {
                    SetColor(12);
                    gotoxy(10,8); cout<<"Ban chua nhap ma doc gia. Vui long nhap!                   ";
                    gotoxy(24,5); cout<<dg;
                    SetColor(14);
                }
                else if(p->soSachDangMuon>3)
                {
                    SetColor(12);
                    gotoxy(10,8); cout<<"Doc gia dang muon 3 quyen sach. Vui long nhap lai!         ";
                    gotoxy(24,5); cout<<dg;
                    SetColor(14);
                }
                else
                {
                    gotoxy(10,8); cout<<"                                                           ";
                    gotoxy(24,5); cout<<dg;
                    gotoxy(0,10); cout<<"Ma doc gia  |      Ho      |            Ten           |    Gioi tinh   |";
                    gotoxy(0,11); cout<<setw(12)<<p->MADG<<"|"<<setw(14)<<p->Ho<<"|"<<setw(26)<<p->Ten<<"|"<<setw(16)<<p->Phai<<"|";
                    co=2;
                    gotoxy(51,5);
                }
            }
            else if(co==2)
            {
                SetBGColor(2);
                int i;
                for(i=0;i<soLuongSach;i++)
                    if(sach[i].MASACH==masach) break;
                if(i==soLuongSach)
                {
                    SetColor(12);
                    gotoxy(10,9); cout<<"Ma sach sai hoac khong ton tai. Vui long nhap lai!";
                    gotoxy(51,5); cout<<masach;
                    SetColor(14);
                }
                else if(masach=="")
                {
                    SetColor(12);
                    gotoxy(10,9); cout<<"Ban chua nhap ma sach. Vui long nhap!             ";
                    gotoxy(51,5); cout<<masach;
                    SetColor(14);
                }
                else if(p->soSachDangMuon>=3)
                {
                    SetColor(12);
                    gotoxy(10,8); cout<<"Doc gia dang muon 3 quyen sach. Vui long nhap lai!";
                    gotoxy(24,5); cout<<dg;
                    SetColor(14);
                }
                else if(masach.size()!=6)
                {
                    SetColor(12);
                    gotoxy(10,9); cout<<"Ma sach phai co 6 ky tu. Vui long nhap lai!       ";
                    gotoxy(51,5); cout<<masach;
                    SetColor(14);
                }
                else if(sach[i].trangThai==1)
                {
                    SetColor(12);
                    gotoxy(10,9); cout<<"Sach da duoc cho muon. Vui long chon sach khac!   ";
                    gotoxy(51,5); cout<<masach;
                    SetColor(14);
                }
                else if(sach[i].trangThai==2)
                {
                    SetColor(12);
                    gotoxy(10,9); cout<<"Sach da bi thanh li. Vui long chon sach khac!     ";
                    gotoxy(51,5); cout<<masach;
                    SetColor(14);
                }
                else
                {
                    gotoxy(10,9); cout<<"                                                  ";
                    gotoxy(51,5); cout<<masach;
                    LayNgayHT(mt.ngayMuon.ngay,mt.ngayMuon.thang,mt.ngayMuon.nam);
                    mt.ngayTra=congNgayThang(mt.ngayMuon,15);
                    gotoxy(10,13); cout<<"So sach ma doc gia da muon: "<<p->soSachDangMuon+1;
                    gotoxy(10,14); cout<<"Ngay muon: "<<mt.ngayMuon.ngay<<"/"<<mt.ngayMuon.thang<<"/"<<mt.ngayMuon.nam;
                    gotoxy(10,15); cout<<"Ngay tra: "<<mt.ngayTra.ngay<<"/"<<mt.ngayTra.thang<<"/"<<mt.ngayTra.nam;
                    gotoxy(0,16); cout<<"Ma sach  |          Ten sach           |      Tac gia     | NXB | VT | ST  "<<endl;
                    gotoxy(0,17); cout<<setw(9)<<sach[i].MASACH<<"|"<<setw(29)<<sach[i].TUASACH<<"|"<<setw(18)<<sach[i].tacGia<<"|"<<setw(5)<<sach[i].NXB<<"|"<<setw(4)<<sach[i].viTri<<"|"<<setw(5)<<sach[i].soTrang;
                    p->soSachDangMuon++;
                    sach[i].soLanMuon++;
                    sach[i].trangThai=1;
                    mt.MASACH=masach;
                    mt.tthai=0;
                    themMuonTra(p->CONTRO,mt);
                }
            }
        }
    }
}
//Dựa vào hàm mã đọc giả tìm được, tìm ra danh sách sách mượn, đổi tình trạng thành da muon(1:da muon, 0:dang muon), giảm số sách đang mượn xuống 1.
void tra()
{
    system("cls");
	system("color 2E");
	gotoxy(20,0); cout<<"****************************************";
	gotoxy(20,1); cout<<"*               TRA SACH               *";
	gotoxy(20,2); cout<<"****************************************";
	gotoxy(30,3); cout<<"Bam ESC de thoat!"<<endl;
	if(soLuongSach==0)
    {
        SetColor(12);
        cout<<"Trong thu vien chua co sach!"<<endl;
        system("Pause");
        return;
    }
    if(DG==NULL)
    {
        SetColor(12);
        cout<<"Trong thu vien chua cho doc gia!"<<endl;
        system("Pause");
        return;
    }
    gotoxy(5,5); cout<<"Nhap tua sach:";
    gotoxy(55,5); cout<<"Nhap ma doc gia:";
    SetBGColor(8);
    gotoxy(20,5); cout<<"                              ";
    gotoxy(71,5); cout<<"      ";
    char tinhTrangSach;
    MT muontra;
    string tuasach;
    string madg;
    int vt;
    char nut;
    int co=1;
    gotoxy(21,5);
    while(1)
    {
        if(co==1)
            vt=21+tuasach.size();
        else if(co==2)
            vt=72+madg.size();
        do
        {
            nut=getch();
        }while(nut!=13&&nut!=27&&nut!=8&&(nut<48||nut>57)&&(nut<97||nut>122)&&nut!=32);
        if(nut==27)
            break;
        else if((nut>=48&&nut<=57)||(nut>=97&&nut<=122)||nut==32)
        {
            if(co==1)
            {
                gotoxy(vt,5);
                if(nut>=97&&nut<=122)
                    nut=nut-32;
                cout<<nut;
                tuasach.insert(tuasach.end(),1,nut);
                vt++;
            }
            else if(co==2&&nut>=48&&nut<=57)
            {
                gotoxy(vt,5);
                cout<<nut;
                madg.insert(madg.end(),1,nut);
                vt++;
            }
        }
        else if(nut==8)
        {
            if(co==1&&tuasach.size()!=0)
            {
                vt--;
                gotoxy(vt,5);
                cout<<" ";
                gotoxy(vt,5);
                tuasach.erase(tuasach.end()-1);
            }
            if(co==2&&madg.size()!=0)
            {
                vt--;
                gotoxy(vt,5);
                cout<<" ";
                gotoxy(vt,5);
                madg.erase(madg.end()-1);
            }
        }
        else if(nut==13)
        {
            int i;
            for(i=0;i<soLuongSach;i++)
                if(sach[i].TUASACH==tuasach) break; //tìm sách nào có tựa sách là tựa vừa nhập
            if(co==1)
            {
                if(tuasach=="")
                {
                    SetColor(12);
                    gotoxy(10,7); cout<<"Ban chua nhap tua sach. Vui long nhap!             ";
                    gotoxy(21,5); cout<<tuasach;
                    SetColor(14);
                }
                else if(i==soLuongSach)
                {
                    SetColor(12);
                    gotoxy(10,7); cout<<"Tua sach sai hoac khong ton tai. Vui long nhap lai!";
                    gotoxy(21,5); cout<<tuasach;
                    SetColor(14);
                }
                else if(sach[i].trangThai==0)
                {
                    SetColor(12);
                    gotoxy(10,7); cout<<"Sach nay chua duoc muon. Vui long nhap lai!        ";
                    gotoxy(21,5); cout<<tuasach;
                    SetColor(14);
                }
                else
                {
                    SetBGColor(2);
                    gotoxy(10,7); cout<<"                                                   ";
                    gotoxy(21,5); cout<<madg;
                    co=2;
                    gotoxy(71,5);
                }
            }
            else if(co==2)
            {
                DDG dg;
                dg=search_dg(atoi(madg.c_str()));
                if(dg==NULL)
                {
                    SetColor(12);
                    gotoxy(10,7); cout<<"Doc gia nay khong ton tai. Vui long nhap lai!      ";
                    gotoxy(72,5); cout<<madg;
                    SetColor(14);
                }
                else
                {
                    SetBGColor(2);
                    gotoxy(10,7); cout<<"                                                   ";
                    gotoxy(72,5); cout<<madg;
                    gotoxy(10,10); cout<<"Xin thong bao tinh trang sach(Tra=T/Lam mat=L): ";
                    do
                    {
                        tinhTrangSach=getch();
                    }while(tinhTrangSach!='t'&&tinhTrangSach!='T'&&tinhTrangSach!='l'&&tinhTrangSach!='L');
                    if(tinhTrangSach=='t'||tinhTrangSach=='T')
                    {
                        sach[i].trangThai=0;
                        for(MUONTRA *p=dg->CONTRO;p!=NULL;p=p->next)
                            if(p->MASACH==sach[i].MASACH)
                                p->tthai=1;
                        dg->soSachDangMuon--;
                        gotoxy(10,11); cout<<"Da tra sach!";
                        Esc();
                        break;
                    }
                    else if(tinhTrangSach=='l'||tinhTrangSach=='L')
                    {
                        for(MUONTRA *p=dg->CONTRO;p!=NULL;p=p->next)
                            if(p->MASACH==sach[i].MASACH)
                                p->tthai=2;
                        gotoxy(10,11); cout<<"Da bao mat sach!";
                        Esc();
                        break;
                    }
                }
            }

        }

    }
}
void delete_tb_mt() //dùng để xóa toàn bộ file mượn trả.
{
    ofstream a("MUONTRA",ios::trunc);
    a.close();
}

void tim_sach()
{
    system("color 2E");
    if(soLuongSach==0)
    {
        gotoxy(10,5);
        SetColor(7);
        cout<<"Chua co quyen sach nao trong thu vien."<<endl;
        system("Pause");
        return;
    }
	gotoxy(10,5); cout<<"Nhap ten sach can tim: ";
	SetBGColor(8);
	gotoxy(34,5); cout<<"                                       ";
	string s;
	int kts[soLuongSach];
	char nut;
	int vt;
    while(1)
    {
        vt=34+s.size();
        do
        {
            nut=getch();
        }while(nut!=13&&nut!=27&&nut!=8&&nut!=32&&(nut<48||nut>57)&&(nut<97||nut>122)&&(nut>65||nut<90));
        if(nut==27)
        {
            break;
        }
        if(nut==13)
        {
            gotoxy(34,5); cout<<s;
            int i;
            int kt=0;
			int u=0;
			for(int v=0;v<=soLuongSach;v++)
			kts[v]=0;
            for(i=0;i<=soLuongSach-1;i++)
			{
                u=0;
                for(int j=0;j<=sach[i].TUASACH.length();j++)
                    if(sach[i].TUASACH[j]==s[u])
                    {
                        u++;
                        if (u==s.length())
                        {
                            u=0;
                            kt=1;
                            kts[i]=1;
                            break;
                        }
                    }
                    else u=0;
            }
            if(kt==0)
            {
                SetColor(7);
                gotoxy(20,7); cout<<"Sach sai hoac khong ton tai. Vui long kiem tra lai!";
                gotoxy(34,5); cout<<s;
            }
            else
            {
                SetBGColor(2);
                gotoxy(20,7); cout<<"                                                   ";
                SetColor(14);
                SetBGColor(2);
                gotoxy(0,8); cout<<"Ma sach  |          Ten sach           |      Tac gia     | NXB | VT | ST  ";
                int ins;
                int kc=0;
                for(ins=0;ins<=soLuongSach;ins++)
			    {
			    	if(kts[ins]==1)
					{
						kc++;
                    gotoxy(0,8+kc); cout<<setw(9)<<sach[ins].MASACH<<"|"<<setw(29)<<sach[ins].TUASACH<<"|"<<setw(18)<<sach[ins].tacGia<<"|"<<setw(5)<<sach[ins].NXB<<"|"<<setw(4)<<sach[ins].viTri<<"|"<<setw(5)<<sach[ins].soTrang<<endl;
            		}
            	}
			}
        }
        else if((nut>=48&&nut<=57)||(nut>=97&&nut<=122)||(nut>=65&&nut<=90)||nut==32)
        {
            gotoxy(vt,5);
            if(nut>=97&&nut<=122)
                nut=nut-32;		//In chu hoa
            SetBGColor(8);
            cout<<nut;
            SetBGColor(2);
            s.insert(s.end(),1,nut);
            vt++;
        }
        else if (nut==8)
        {
            if (s.size()!=0)
            {
                vt--;
                gotoxy(vt,5);
                SetBGColor(8);
                cout<<" ";
                SetBGColor(2);
                gotoxy(vt,5);
                s.erase(s.end()-1);
            }
        }
    }
}
void InDS_10sach_muon_nhieuNhat()
{
    system("Color 2E");
    system("cls");
    gotoxy(20,0); cout<<"****************************************";
	gotoxy(20,1); cout<<"*   TOP 10 SACH DUOC MUON NHIEU NHAT   *";
	gotoxy(20,2); cout<<"****************************************";
	gotoxy(30,3); cout<<"Bam ESC de thoat!";
    if (soLuongSach==0)
    {
        gotoxy(10,5);
        SetColor(12);
        cout<<"Khong co sach trong thu vien "<<endl;
        system("Pause");
        return;
    }
    char k = 179;
    int y = wherey()+1;
    gotoxy(0,5); cout<<" STT |  Ma sach  |           Ten sach           |      Tac gia     |Vi tri|SLM|";
    int co[max] = {0};
    int vitri;  //vị trí của sách trong danh sách đặc và trong mảng cờ.
    int dem = 0;
    int Max;
    while (dem<soLuongSach)
    {
        for (int i=0;i<soLuongSach;i++)
            if (co[i]==0)
            {
                Max=sach[i].soLanMuon;
                vitri=i;
            }
        for (int i=0;i<soLuongSach;i++)
        {
            if (sach[i].soLanMuon>Max&&co[i]==0)
            {
                Max=sach[i].soLanMuon;
                vitri=i;
            }
        }
        co[vitri]=1;
        y=wherey();
        gotoxy(0,y+1); cout<<setw(5)<<dem+1<<"|"<<setw(11)<<sach[vitri].MASACH<<"|"<<setw(30)<<sach[vitri].TUASACH<<"|"<<setw(18)<<sach[vitri].tacGia<<"|"<<setw(6)<<sach[vitri].viTri<<"|"<<setw(3)<<sach[vitri].soLanMuon<<"|";
        dem++;
        if (dem==10) break;
    }
    Esc();
}
void xoa_tb_duLieu(DDG &goc)
{
    gotoxy(20,20); cout<<"Toan bo du lieu se bi xoa. Ban co chac? (Y/N)";
    char nut;
    do
    {
        nut=getch();
    }while(nut!='y'&&nut!='Y'&&nut!='N'&&nut!='n');
    if(nut=='y'||nut=='Y')
    {
        delete_tb_mt();
        clearlist_tree_LRN(DG);
        delete_tb_dg();
        delete_tb_sach();
        soLuongSach=0;
        gotoxy(20,20); cout<<"**********************************************";
        gotoxy(20,21); cout<<"*            Xoa thanh cong!                 *";
        gotoxy(20,22); cout<<"*     Nhan Esc hoac Enter de quay lai!       *";
        gotoxy(20,23); cout<<"**********************************************";
        do
        {
            nut=getch();
        }while(nut!=27&&nut!=13);
        return;
    }
    else
        return;
}
void Insert_dsQuaHan(QH &QH_First, int madg,string masach,int thoiGian)// dùng để thêm vào danh sách quá hạn.
{
    QH p;
    p=new dsQuaHan;
    p->madg=madg;
    p->masach=masach;
    p->thoiGianQuaHan=thoiGian;
    p->next=QH_First;
    QH_First=p;
}
void Sapxep_dsQuaHan(QH &QH_First)  //cái này là selection sort, dùng để sắp lại danh sách quá hạn trước khi in ra.
{
    QH p,q, pmax;
    int qhmax,mdg;
    string ms;
    for(p=QH_First;p->next!=NULL;p=p->next)
    {
        qhmax=p->thoiGianQuaHan;
        mdg=p->madg;
        ms=p->masach;
        pmax=p;
        for(q=p->next;q!=NULL;q=q->next)
            if(qhmax<q->thoiGianQuaHan)
            {
                qhmax=q->thoiGianQuaHan;
                mdg=q->madg;
                ms=q->masach;
                pmax=q;
            }
        pmax->madg=p->madg;
        pmax->masach=p->masach;
        pmax->thoiGianQuaHan=p->thoiGianQuaHan;

        p->madg=mdg;
        p->masach=ms;
        p->thoiGianQuaHan=qhmax;
    }
}
int doiDangNgayThang_so(ngay ng)
{
    int sn;
    if((ng.nam%4)==0)
    {
        if(ng.thang==1)     return sn=ng.ngay+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==2)     return sn=ng.ngay+31+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==3)     return sn=ng.ngay+29+31+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==4)     return sn=ng.ngay+29+31*2+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==5)     return sn=ng.ngay+29+30+31*2+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==6)     return sn=ng.ngay+29+30+31*3+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==7)     return sn=ng.ngay+29+30*2+31*3+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==8)     return sn=ng.ngay+29+30*2+31*4+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==9)     return sn=ng.ngay+29+30*2+31*5+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==10)    return sn=ng.ngay+29+30*3+31*5+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==11)    return sn=ng.ngay+29+30*3+31*6+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==12)    return sn=ng.ngay+29+30*4+31*6+ng.nam/4*(365*3+366)+ng.nam%4*365;
    }
    else
    {
        if(ng.thang==1)     return sn=ng.ngay+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==2)     return sn=ng.ngay+31+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==3)     return sn=ng.ngay+28+31+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==4)     return sn=ng.ngay+28+31*2+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==5)     return sn=ng.ngay+28+30+31*2+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==6)     return sn=ng.ngay+28+30+31*3+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==7)     return sn=ng.ngay+28+30*2+31*3+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==8)     return sn=ng.ngay+28+30*2+31*4+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==9)     return sn=ng.ngay+28+30*2+31*5+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==10)    return sn=ng.ngay+28+30*3+31*5+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==11)    return sn=ng.ngay+28+30*3+31*6+ng.nam/4*(365*3+366)+ng.nam%4*365;
        if(ng.thang==12)    return sn=ng.ngay+28+30*4+31*6+ng.nam/4*(365*3+366)+ng.nam%4*365;
    }
}
int truNgayThang(ngay ngTra)
{
    int soNgay,iToDay,iNgTra;
    ngay toDay;
    LayNgayHT(toDay.ngay,toDay.thang,toDay.nam);
    iToDay=doiDangNgayThang_so(toDay);
    iNgTra=doiDangNgayThang_so(ngTra);
    return soNgay=iToDay-iNgTra;
}
void Clearlist_qh(QH &QH_First)
{
    QH p;
    while(QH_First!=NULL)
    {
        p=QH_First;
        QH_First=QH_First->next;
        free(p);
    }
}
void in_ds_quaHan()
{
    system("cls");
	system("color 2E");
	gotoxy(20,0); cout<<"****************************************";
	gotoxy(20,1); cout<<"*    DANH SACH DOC GIA MUON QUA HAN    *";
	gotoxy(20,2); cout<<"****************************************";
	gotoxy(30,3); cout<<"Bam ESC de thoat!";
    DDG Stack[max];
    int sp=-1;
    DDG p=DG;
    while(p!=NULL)
    {
        for(MT mt=p->CONTRO;mt!=NULL;mt=mt->next)
            if(mt->tthai==0)
                if(truNgayThang(mt->ngayTra)>0)
                {
                    int thoigian;
                    thoigian=truNgayThang(mt->ngayTra);
                    Insert_dsQuaHan(QH_First,p->MADG,mt->MASACH,thoigian);
                }
        if(p->right!=NULL)
            Stack[++sp]=p->right;
        if(p->left!=NULL)
            p=p->left;
        else if(sp==-1)
            break;
        else
            p=Stack[sp--];
    }
    //sau khi chạy hết toàn bộ mượn trả, lọc những phiếu quá hạn, cho vào ds_quaHan, thì sắp xếp danh sách quá hạn lại.
    if(QH_First==NULL)
    {
        gotoxy(10,5); cout<<"Khong co doc gia nao muon qua han";
        Esc();
        return;
    }
    else
    {
        Sapxep_dsQuaHan(QH_First);
        //sau khi sắp xếp, thì duyệt in.
        gotoxy(0,6); cout<<" STT |    Ho    |           Ten         |          Ten sach          |QH(ngay)|";
        QH qh;
        qh=QH_First;
        int dem=0;
        while(qh!=NULL)
        {
            int i;
            for(i=0;i<soLuongSach;i++)
                if(sach[i].MASACH==qh->masach) break;
            DDG dg;
            dg=search_dg(qh->madg);
            dem++;
            gotoxy(0,6+dem);
            cout<<setw(5)<<dem<<"|"<<setw(10)<<dg->Ho<<"|"<<setw(23)<<dg->Ten<<"|"<<setw(28)<<sach[i].TUASACH<<"|"<<setw(8)<<qh->thoiGianQuaHan<<"|";
            qh=qh->next;
        }
    }
    Clearlist_qh(QH_First);
    Esc();
}
void tim_muonTra_theo_tenSach()
{
    system("cls");
    system("color 2E");
    gotoxy(20,0); cout<<"****************************************";
	gotoxy(20,1); cout<<"* TIM THONG TIN MUON TRA THEO TEN SACH *";
	gotoxy(20,2); cout<<"****************************************";
    if(soLuongSach==0)
    {
        gotoxy(10,5);
        SetColor(7);
        cout<<"Chua co quyen sach nao trong thu vien."<<endl;
        system("Pause");
        return;
    }
	gotoxy(10,5); cout<<"Nhap ten sach can tim: ";
	SetBGColor(8);
	gotoxy(34,5); cout<<"                                       ";
	string s;
	int kt=0;
	char nut;
	int vt;
    while(1)
    {
        vt=34+s.size();
        do
        {
            nut=getch();
        }while(nut!=13&&nut!=27&&nut!=8&&nut!=32&&(nut<48||nut>57)&&(nut<97||nut>122)&&(nut>65||nut<90));
        if(nut==27)
        {
            break;
        }
        else if((nut>=48&&nut<=57)||(nut>=97&&nut<=122)||(nut>=65&&nut<=90)||nut==32)
        {
            gotoxy(vt,5);
            if(nut>=97&&nut<=122)
                nut=nut-32;		//In chu hoa
            SetBGColor(8);
            cout<<nut;
            s.insert(s.end(),1,nut);
            vt++;
        }
        else if (nut==8)
        {
            if (s.size()!=0)
            {
                vt--;
                gotoxy(vt,5);
                SetBGColor(8);
                cout<<" ";
                gotoxy(vt,5);
                s.erase(s.end()-1);
            }
        }
        else if(nut==13)
        {
            gotoxy(34,5); cout<<s;
            int i;
            for(i=0;i<=soLuongSach-1;i++)     //Chạy từ 0 đến hết danh sách -1 của sách(vi khoi dong sls =0)
                if(sach[i].TUASACH==s) break;    //nếu tìm thấy tên trùng thì thoát vòng for.
            MT mt;
            DDG Stack[max];
            int sp=-1;
            DDG p=DG;
            while(p!=NULL)
            {
                for(mt=p->CONTRO;mt!=NULL;mt=mt->next)
                    if(mt->tthai==0)
                        if(mt->MASACH==sach[i].MASACH)
                        {
                            break;
                        }
                if(p->right!=NULL)
                    Stack[++sp]==p->right;
                if(p->left!=NULL)
                    p=p->left;
                else if(sp==-1)
                    break;
                else
                    p=Stack[sp--];
            }
            if(i==soLuongSach)
            {
                SetColor(7);
                gotoxy(20,7); cout<<"Sach sai hoac khong ton tai. Vui long kiem tra lai!";
                gotoxy(34,5); cout<<s;
            }
            else if(mt!=NULL&&mt->tthai==0)
            {
                SetBGColor(2);
                gotoxy(20,7); cout<<"                                                   ";
                SetColor(14);
                SetBGColor(2);
                gotoxy(0,8); cout<<"Ma sach  |          Ten sach           |      Tac gia     | NXB | VT | ST  ";
                gotoxy(0,9); cout<<setw(9)<<sach[i].MASACH<<"|"<<setw(29)<<sach[i].TUASACH<<"|"<<setw(18)<<sach[i].tacGia<<"|"<<setw(5)<<sach[i].NXB<<"|"<<setw(4)<<sach[i].viTri<<"|"<<setw(5)<<sach[i].soTrang;
                gotoxy(20,10); cout<<"Ngay muon: "<<mt->ngayMuon.ngay<<"/"<<mt->ngayMuon.thang<<"/"<<mt->ngayMuon.nam;
                gotoxy(20,11); cout<<"Ngay tra: "<<mt->ngayTra.ngay<<"/"<<mt->ngayTra.thang<<"/"<<mt->ngayTra.nam;
                gotoxy(20,12); cout<<"Nguoi muon: "<<p->Ho<<" "<<p->Ten;
            }
            else if(mt!=NULL&&mt->tthai==2)
            {
                SetBGColor(2);
                gotoxy(20,7); cout<<"                                                   ";
                SetColor(14);
                SetBGColor(2);
                gotoxy(0,8); cout<<"Ma sach  |          Ten sach           |      Tac gia     | NXB | VT | ST  ";
                gotoxy(0,9); cout<<setw(9)<<sach[i].MASACH<<"|"<<setw(29)<<sach[i].TUASACH<<"|"<<setw(18)<<sach[i].tacGia<<"|"<<setw(5)<<sach[i].NXB<<"|"<<setw(4)<<sach[i].viTri<<"|"<<setw(5)<<sach[i].soTrang;
                gotoxy(20,10); cout<<"Sach da bi lam mat!                  ";
                gotoxy(20,11); cout<<"Vui long doi giai quyet sau!         ";
                gotoxy(20,12); cout<<"                                     ";
            }
            else
            {
                SetBGColor(2);
                gotoxy(20,7); cout<<"                                                   ";
                SetColor(14);
                SetBGColor(2);
                gotoxy(0,8); cout<<"Ma sach  |          Ten sach           |      Tac gia     | NXB | VT | ST  ";
                gotoxy(0,9); cout<<setw(9)<<sach[i].MASACH<<"|"<<setw(29)<<sach[i].TUASACH<<"|"<<setw(18)<<sach[i].tacGia<<"|"<<setw(5)<<sach[i].NXB<<"|"<<setw(4)<<sach[i].viTri<<"|"<<setw(5)<<sach[i].soTrang;
                gotoxy(20,10); cout<<"Co the cho muon!                     ";
                gotoxy(20,11); cout<<"                                     ";
                gotoxy(20,12); cout<<"                                     ";
            }
        }
    }
}
//////////////
///MAIN///////
//////////////

int main()
{
    doc_file_sach();
    doc_file_dg();
    char nut;
	do
	{
		giaoDien_chinh();
        giaoDien_bangChon();
		switch(chon)
		{
        	case 1:
                giaoDien_nhap_sach();
                nhap_sach();
                break;
            case 2:
                do
                {
                    giaoDien_tl_sach();
                    thanhLy_sach();
                    cout<<endl;
                    cout<<"Ban muon thanh ly tiep khong?(Y/N)";
                    nut=getch();
                }while(nut=='y'||nut=='Y');
                break;
            case 3:
                do
                {
                    giaoDien_tim_sach();
                    tim_sach();
                    cout<<endl;
                    cout<<"Ban muon tim tiep khong?(Y/N)";
                    nut=getch();
                }while(nut=='y'||nut=='Y');
               	break;
            case 6:
                InDS_10sach_muon_nhieuNhat();
                break;
            case 7:
                do
                {
                    giaoDien_nhap_docGia();
                    nhap_dg();
                    cout<<endl;
                    cout<<"Ban muon nhap tiep khong?(Y/N)";
                    nut=getch();
                }while(nut=='y'||nut=='Y');
                break;
            case 8:
                do
                {
                    giaoDien_tim_docGia();
                    tim_dg();
                    cout<<endl;
                    cout<<"Ban muon tim tiep khong?(Y/N)";
                    nut=getch();
                }while(nut=='y'||nut=='Y');
               	break;
            case 9:
        		giaoDien_xoa_docGia();
              	xoa_dg(DG);
				break;
            case 10:
                in_ds_quaHan();
                break;
            case 13:
                muon();
                break;
            case 14:
                tra();
                break;
            case 15:
                tim_muonTra_theo_tenSach();
                break;
           	case 16:
                xoa_tb_duLieu(DG);
           		break;
        }
    }while(chon!=17);
/////////
    system("cls");
	gotoxy(10,10);     cout<<"**********************************************************";
	gotoxy(10,11);     cout<<"*Ban co muon luu toan bo cong viec truoc khi thoat khong?*";
	gotoxy(10,12);     cout<<"*                   Bam Enter: Co!                       *";
	gotoxy(10,13);     cout<<"*                   Bam ESC  : Khong!                    *";
	gotoxy(10,14);     cout<<"**********************************************************";
    do
    {
       	nut=getch();
    }while(nut!=13&&nut!=27);
    if(nut==13)
    {
        luu_file_sach();
        luu_file_dg();
        gotoxy(10,10); cout<<"**********************************************************";
		gotoxy(10,11); cout<<"*                     LUU THANH CONG!                    *";
		gotoxy(10,12); cout<<"*                                                        *";
		gotoxy(10,13); cout<<"*                       HEN GAP LAI!                     *";
		gotoxy(10,14); cout<<"**********************************************************";
    }
    else
    {
    	gotoxy(10,10); cout<<"**********************************************************";
		gotoxy(10,11); cout<<"*                                                        *";
		gotoxy(10,12); cout<<"*                       HEN GAP LAI!                     *";
		gotoxy(10,13); cout<<"*                                                        *";
		gotoxy(10,14); cout<<"**********************************************************";
    }
}

