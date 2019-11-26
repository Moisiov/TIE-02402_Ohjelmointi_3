#include <QtTest>

#include "handlers/gameeventhandler.hh"
#include "handlers/objectmanager.hh"

// add necessary includes here

class ObjectManagerTesting : public QObject
{
    Q_OBJECT

public:
    ObjectManagerTesting();
    ~ObjectManagerTesting() = default;

private slots:
    void initTestCase();
    void test_case1();
    void test_case2();

private:
    std::shared_ptr<GameEventHandler> _GEHandler;
    std::shared_ptr<ObjectManager> _objM;
};

ObjectManagerTesting::ObjectManagerTesting()
{

}

void ObjectManagerTesting::initTestCase()
{
    _GEHandler = std::make_shared<GameEventHandler>();
    _objM = std::make_shared<ObjectManager>();
    _GEHandler->setGEHandler(_GEHandler);
    _objM->setGEHandler(_GEHandler);
    _GEHandler->setObjectManager(_objM);
    _objM->setObjManager(_objM);
}

void ObjectManagerTesting::test_case1()
{

}

void ObjectManagerTesting::test_case2()
{

}

QTEST_APPLESS_MAIN(ObjectManagerTesting)

#include "tst_objectmanagertesting.moc"
