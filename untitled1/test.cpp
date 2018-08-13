#include "test.h"
#include "ui_test.h"
#include <QCoreApplication>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QProcess>
#include <QProcessEnvironment>
#include <vector>
#include <unordered_map>
#include <QPdfWriter>
#include <QPainter>
#include <QPoint>
#include <QtMath>
#include <queue>
#include <windows.h>
#include <string>
#include <sstream>
QTextStream cout(stdout);

test::test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
}

test::~test()
{
    delete ui;
}

std::vector<QString> params;
QString Ins1(){
    QString out="cout << curr << \" \" << parent << \"  |  \"<<";
    for(int i=0;i<params.size();i++){
        out.append(params[i]);
        out.append(" << \"  \" << ");
    }
    out.append("endl;\n");
    return out;

}




QString Ins2(){
    cout<<"INS2 Called"<<endl;
    QString out=",++c,x";
    return out;

}


void test::on_pushButton_clicked()
{
         ui->textEdit->clear();
         params.push_back("l");
         params.push_back("r");
         //params.push_back("val");

         cout<<"HHHHHH"<<endl;
         QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
         QFile file(fileName);
         currentFile = fileName;
         if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
         }
        setWindowTitle(fileName);
        QTextStream in(&file);
//        QString text = in.readAll();
        QString l;
        bool firstocc=0;
        std::vector<QString> v;
        v.clear();
        int lastins=0;
        int m=1;
        int lastpos=0;
        while(1){
              l=in.readLine();
                int k=0;
                int j=0;
                bool done=0;
                int ret=0;int rec=0;
                if(((k = l.indexOf("return", k)) != -1)&&m){
                    cout<<k<<endl;
                    l.replace(k,6,"int y= ");
                    QString t3=l;
                    l.push_back('\n');

                    ret=1;
                    done=1;
                    l=t3;
                }
                if(((j = l.indexOf("rec", j)) != -1)&&m){
                    rec=1;
                   int curr=j;
                   if(!firstocc){
                       while(curr<l.length()&&l[curr]!=')') curr++;
                       l.insert(curr,",int curr,int parent");

                       firstocc=1;
                       l.push_back('\n');
                       v.push_back(l);
                       v.push_back(" int x=curr;\n");
                       v.push_back(Ins1());
                       done=1;
                   }else{
                    while(curr<l.size()-1){
                        cout<<curr<<endl;
                        while(curr<l.length()&&l[curr]!=')') curr++;
                        if(curr==l.length()-1) break;
                        l.insert(curr,Ins2());
                        done=1;
                        while(curr<l.length()&&l[curr]!=')') curr++;
                        curr++;
                    }
                    l.push_back('\n');
                    v.push_back(l);
                    lastpos=v.size()-1;
                   }

                }
                if(!done){
                    if(l.indexOf("main",0)!=-1) m=0;
                    l.push_back('\n');
                    v.push_back(l);
                }
                if(ret) {
                   if (!rec) v.push_back(l);
                    v.push_back("cout<<x<<\"$\"<<y<<endl; \n");
                    v.push_back("return y;\n");
                }
               if(in.atEnd()) break;
        }
        QString temp=v[lastpos];

        QString out="";
        for(int i=0;i<v.size();i++){
           if(i!=lastins) out.append(v[i]);
        }

        ui->textEdit->setText(out);
        file.close();
//        render();
}

int leadindex=0; // to increment graph keys
std::unordered_map<int,int> to_key; //stores curr-> graph keys
std::unordered_map<int,int> val;
std::unordered_map<int,std::string> val1;//stores var values
std::map<int,QRectF> R; //id-> QRectF
std::vector<std::vector<int>> g; // graph


void test::bfs(){
    cout<<"Clicked"<<endl;
    QString fileName = tr("test.pdf");
    QPdfWriter pdf(fileName);
    QPainter painter(&pdf);
    // add ch   ildren to the current element at a fixed distance and angles according to the number of children
    std::queue<int> q;
    q.push(0);
    int length=3000;
    painter.drawRect(R[0]);
    while(!q.empty()){
        int parent=q.front();
        cout<<"Parent = "<<parent<<endl;
        q.pop();
        int number=g[parent].size();
        double ang= qDegreesToRadians(180.0/(double)(number+1));
        cout<<ang<<endl;
        QPointF cent=R[parent].center();
        cout<<"P = "<<R[parent].x()<<" "<<R[parent].y()<<endl;
        for(int i=0;i<g[parent].size();i++){
               cout<<"Child = "<<g[parent][i]<<endl;
               QPointF temp1(cent.x()+length*qCos((i+1)*ang),cent.y()+length*qSin((i+1)*ang)) ;
               R[g[parent][i]].moveCenter(temp1);
               painter.drawLine(cent,temp1);
               cout<<"R = "<<R[g[parent][i]].x()<<" "<<R[g[parent][i]].y()<<endl;
               q.push(g[parent][i]);
        }

    }
    cout<<"Done"<<endl;
    for(auto it=to_key.begin();it!=to_key.end();it++){
        cout<<"HHH"<<endl;
        //create rec and
        cout<<R[it->first].x()<<"%%"<<R[it->first].y()<<endl;
        painter.drawRect(R[it->first]);
        QString str;
        str = QString("%1")
                .arg(it->first);
        QRectF d=R[it->first];
        QString str1="Value ="+QString::number(val[it->first]);
        QString str2;
        std::stringstream ss(val1[it->first]);
        std::string a[2];
        std::getline(ss,a[0],' ');
        std::getline(ss,a[1],' ');
        cout<<QString::fromStdString(val1[it->first])<<endl;
        cout<<QString::fromStdString(a[0])<<endl;
        cout<<QString::fromStdString(a[1])<<endl;
        for(int i=0;i<params.size();i++){
            cout<<"YYYYY"<<endl;
            str2.append(params[i]);
            str2.append(" = ");
            str2.append( QString::fromStdString(a[i]));
            str2.append("");
        }
        QPointF d1=d.center();
        QPointF d2=d.center();
        d1.rx()-=500;
        d2.rx()-=500;
        d2.ry()+=150;
        painter.drawText(d,str);
        painter.drawText(d1,str1);
        painter.drawText(d2,str2);
    }


}


void test::render(){
    //Open Pdf and start writing


    //make all links
    QPoint st(4500,-2000);
    QSize sz(1250,1000);
    int offset=1000;
    for(auto it=to_key.begin();it!=to_key.end();it++){
        //create rec and add to map R
        QRectF r1(st,sz);
        st.ry()+=offset;
        R[it->first]=r1;
//         painter.drawRect(r1);
    }
    bfs();
    cout<<"Rendered :"<<endl;
    return;



}



void test::on_pushButton_2_clicked()
{
       // If we don't have a filename from before, get one.
       QFile file("output.cpp");
       QFileInfo info("output.cpp");
       cout<< info.absoluteDir().absolutePath();

       if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
           return;
       }
////       setWindowTitle(fileName);
       QTextStream out(&file);
       QString text = ui->textEdit->toPlainText();
       out << text;
       file.close();
////           QObject *parent=//current provcess;
       QString program = "C:/cygwin64/bin/g++";
       QStringList arguments;
       arguments <<"output.cpp";
       cout<<"Here"<<endl;
       QProcess *myProcess = new QProcess();
       myProcess->start(program, arguments);
       QString program1 = "a.exe";
       QProcess *myProcess1 = new QProcess();
       myProcess1->start(program1);
       Sleep(200); //wait for output to get generated
       cout<<"GGG"<<endl;
       //read data from output
       QString fileName1 = "output.txt";
       QFile file1(fileName1);
       if (!file1.open(QIODevice::ReadOnly | QFile::Text)) {
          QMessageBox::warning(this, "Warning", "Cannot open file: " + file1.errorString());
          return;
       }
      QTextStream in(&file1);
      QString l;
      l=in.readLine();
      g.resize(200);
      while(1){
             l=in.readLine();
//             cout<<l<<endl;
             int k=0;
             std::string s=l.toStdString();
             if(((k = l.indexOf("$", k)) != -1)){
                    // insert val
                 std::stringstream ss(s);
                 int a,b;
                 std::string s;
                 getline(ss,s,'$');
                 a=std::stoi(s);
                 getline(ss,s,'$');
                 b=std::stoi(s);
                 cout<<a<<" SS "<<b<<endl;
                 val[a]=b;
             }else{
                  std::stringstream ss(s);
                  int a,b;
                  ss>>a>>b;
                  cout<<a<<" ^^ "<<b<<endl;
                  if(to_key.find(a)==to_key.end()){
                      to_key[a]=1;
                  }
                  if(to_key.find(b)==to_key.end()){
                      to_key[b]=1;
                  }
                  g[b].push_back(a);
                  int yy = l.indexOf("|", 0);
                  std::string t=l.toStdString().substr(yy+1);
                  getline(ss,t);
                  val1[a]=t;
                 // fill up graph
             }

             if(in.atEnd()) break;
      }
      cout<<"Here"<<endl;
      for(int i=0;i<g.size();i++){
          for(int j=0;j<g[i].size();j++){
              cout<<g[i][j]<<" ";
          }cout<<endl;
      }

      //end read data

     render();

}
