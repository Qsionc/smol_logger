#include <iostream>
#include <gtest/gtest.h>
#include <implementation/jthread.h>
#include <implementation/logger_queue.h>

class TestSmoggerLibraryFixture : public ::testing::Test {
public:
    ~TestSmoggerLibraryFixture() override = default;

protected:
    void SetUp() override {
        Test::SetUp();
    }

    void TearDown() override {
        Test::TearDown();
    }
};

TEST_F(TestSmoggerLibraryFixture, test_jthread) {
    std::stringstream ss;
    std::string message = "Jthread test";
    auto callable = [&](auto k) { ss << k; };
    smol::jthread jthread(callable, message);
    jthread.join();
    ASSERT_EQ(ss.str(), message);
}

TEST_F(TestSmoggerLibraryFixture, test_jthread_autojoin) {
    {
        smol::jthread jthread = smol::jthread([]() {});
    }
}

TEST_F(TestSmoggerLibraryFixture, test_message_queue) {
    smol::logger_queue queue;
    std::string test_message = "Test Message";
    smol::jthread jthread([&]() {
        queue.put_message(test_message);
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    ASSERT_FALSE(queue.empty());
    auto result = queue.get_next();
    ASSERT_EQ(*result, test_message);
}

int main(int _argc, char** _argv) {
    ::testing::InitGoogleTest(&_argc, _argv);
    return RUN_ALL_TESTS();
}