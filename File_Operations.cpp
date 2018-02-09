#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include "File_Operations.h"
#include <QFile>
#include <QFileInfo>

//新建文件
//fileName:路径和文件名
void New_File(QString fileName)
{
    QFileInfo fi(fileName);
    if(fi.isFile())
    {
        qDebug("file ecist!\n");
    }
    else
    {
        QFile f(fileName);
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        f.close();
    }
}

//新建密码文件
//fileName:路径和文件名
//passwd：初始密码
void New_PasswdFile(QString fileName , QString passwd)
{
    QFileInfo fi(fileName);
    if(fi.isFile())
    {
        qDebug("file ecist!\n");
    }
    else
    {
        QFile f(fileName);
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&f);
        out<<passwd<<endl;        //填入初始密码
        out.flush();
        f.close();
    }
}

//清空文件
//fileName：要清空文件的文件名
void empty_file(QString fileName)
{
    QFile f(fileName);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        printf("Open file failed!");
    }
    f.close();
}

//如果是5行，nNum最大为4
void DeleteOneline(int nNum, QString &strall)
{
    int nLine=0;
    int Index=0;
    //算出行数nLine
    while(Index!=-1)
    {
        Index=strall.indexOf('\n',Index+1);
        nLine++;
    }

    //如果是直接从位置0开始删除\n算一个字符"abc\nme\ndo" \n的index是3要删除3+1个字符，即index+1个
    if(nNum==0)
    {
        int nIndex=strall.indexOf('\n');
        strall.remove(0,nIndex+1);
    }
    else
    {
        int nTemp=nNum;
        int nIndex=0,nIndex2=0;
        while(nTemp--)
        {
            //
            nIndex=strall.indexOf('\n',nIndex+1);//这里会更新nIndex
            if(nIndex!=-1)//说明是有效的
            {
                nIndex2=strall.indexOf('\n',nIndex+1);
            }
        }
        //删除的行不是最后一行（从nIndex+1这个位置起nIndex2-nIndex个字符全部抹去）
        if(nNum<nLine-1)
        {
            strall.remove(nIndex+1, nIndex2-nIndex);//不用减一
        }
        //删除的是最后一行（从nIndex起始len-nIndex个字符全抹去）
        //不能从nIndex+1处开始，
        else if(nNum==nLine-1)
        {
            int len=strall.length();
            strall.remove(nIndex,len-nIndex);
        }
        else
        {

        }

    }
}

//删除文件的一行
void deleteOnelineInFile(int nNumLine, QString filename)
{
    QString strall;
    QFile readfile(filename);
    if(readfile.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&readfile);
        strall=stream.readAll();
    }
    readfile.close();
    DeleteOneline(nNumLine, strall);

    QFile writefile(filename);
    if(writefile.open(QIODevice::WriteOnly))
    {
        QTextStream wrtstream(&writefile);
        wrtstream<<strall;
    }
    writefile.close();
}

//写动态监控文件，这个函数没用到
void DataMonitor_In_File(QString file , double time , double voltage , double current)
{
    QFile f(file);
    if(!(f.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)))
    {
        qDebug("---Open failed!---\n");
        return;
    }
    QTextStream txtInput(&f);
    txtInput << time << "   " << voltage << "   " << current << endl;
}
