#include <QtTest>

#include "gameeventhandler.hh"
#include "objectmanager.hh"

// add necessary includes here

class GameEventHandlerTesting : public QObject
{
    Q_OBJECT

public:
    GameEventHandlerTesting();
    ~GameEventHandlerTesting() = default;

private slots:
    void initTestCase();
    void test_case1();

private:
    std::shared_ptr<GameEventHandler> _GEHandler;
    std::shared_ptr<ObjectManager> _objM;
};

GameEventHandlerTesting::GameEventHandlerTesting():
    _GEHandler(nullptr),
    _objM(nullptr)
{

}

void GameEventHandlerTesting::initTestCase()
{
    /*
    _GEHandler = std::make_shared<GameEventHandler>();
    _objM = std::make_shared<ObjectManager>();
    _GEHandler->setGEHandler(_GEHandler);
    _objM->setGEHandler(_GEHandler);
    _GEHandler->setObjectManager(_objM);
    _objM->setObjManager(_objM);
    */
}

void GameEventHandlerTesting::test_case1()
{

}

QTEST_APPLESS_MAIN(GameEventHandlerTesting)

#include "tst_gameeventhandlertesting.moc"
