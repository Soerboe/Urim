#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <QtTest>
#include <iostream>

namespace TestRunner
{
class TestSetup {
public:
    TestSetup() : _singleTest(0) {}
    QList<QObject*> tests() {return _tests;}

    void registerTest(QObject* test, bool singleTest) {
        _tests.append(test);

        if (singleTest) {
            if (_singleTest) {
                std::cerr << "ERROR: Multiple single tests registered, running the first registered test" << std::endl;
            } else {
                _singleTest = test;
            }
        }

    }

    QObject* singleTest() {return _singleTest;}

    void cleanUp() {
        foreach(QObject* test, _tests) {
            delete test;
        }
    }

private:
    QList<QObject*> _tests;
    QObject* _singleTest;
};

inline TestSetup& testSetup() {
    static TestSetup setup;
    return setup;
}

inline int run(int argc, char** argv) {
    int result = 0;
    int testClassesRun = 0;
    auto RUN_TEST = [&result, &testClassesRun, argc, argv](QObject* obj) {
        result |= QTest::qExec(obj, argc, argv);
        testClassesRun++;
    };

    TestSetup& testSetup = TestRunner::testSetup();
    if (testSetup.singleTest()) {
        std::cout << "INFO: Running only the test registered as single test" << std::endl;
        RUN_TEST(testSetup.singleTest());
    } else {
        foreach(QObject* test, testSetup.tests()) {
            RUN_TEST(test);
        }
    }

    std::cout << testClassesRun << " test class(es) executed" << std::endl;

    testSetup.cleanUp();
    return result; \
}

template <typename T>
class Test {
public:
    Test(bool singleTest) {
        testSetup().registerTest(new T, singleTest);
    }
};

#define REGISTER_TEST(className) static TestRunner::Test<className> test(false);
#define REGISTER_SINGLE_TEST(className) static TestRunner::Test<className> test(true);
#define TESTRUNNER_MAIN int main(int argc, char** argv) {return TestRunner::run(argc, argv);}

} // namespace

#endif // TESTRUNNER_H
