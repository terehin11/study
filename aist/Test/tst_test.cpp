#include <QtTest>
#include "../AistFlightRoute/src/flightplan.h"
#include "../AistFlightRoute/src/serializable.h"
// add necessary includes here

class Test : public QObject
{
    Q_OBJECT

public:
    Test();
    ~Test();
private slots:

    void Test_file();
};

Test::Test()
{

}

Test::~Test()
{

}


void Test::Test_file()
{
    //Test Json read functional

        QString str;
        QFile file("flightplan.plan");
        if(file.open(QIODevice::ReadOnly))
        {
            str = file.readAll();
            file.close();
        }
    QJsonObject obj;
  QJsonDocument doc = QJsonDocument::fromJson(str.toLocal8Bit());
  if(!doc.isNull())
     {
         if(doc.isObject())
         {
             obj = doc.object();
         }
         else
         {
             qDebug() << "Document is not an object" << endl;
         }
     }
     else
     {
         qDebug() << "Invalid JSON...\n" << str << endl;
     }
  FlightPlan fp;
  fp.loadFromJson(obj);
  obj = fp.toJson();
  QString test_str_check;
  QFile file2("test.plan");
  if(file2.open(QIODevice::ReadWrite ))
  {
      QJsonDocument doc2(obj);
      QByteArray bytes = doc2.toJson();
      file2.write(bytes);
      file2.close();
  }
  if(file2.open(QIODevice::ReadWrite ))
  {
    test_str_check = file2.readAll();
    file2.close();
  }


  QCOMPARE(test_str_check,str);
}

QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"
