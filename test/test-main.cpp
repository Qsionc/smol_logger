#include <iostream>
#include <gtest/gtest.h>
#include <singleton.h>
#include <core/jthread.h>
#include <core/logger_queue.h>
#include <core/logger_reader.h>
#include "smogger.h"

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
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    ASSERT_FALSE(queue.empty());
    auto result = queue.get_next();
    ASSERT_EQ(*result, test_message);
}

TEST_F(TestSmoggerLibraryFixture, test_logger_reader) {
    smol::singleton<smol::logger_reader> reader;
    smol::singleton<smol::logger_queue> queue;
    std::string test_message = "Test Message";
    std::stringstream ss;

    queue.init();
    reader.init();
    reader->run(*queue);

    reader->bind_sink("ss", &ss);
    queue->put_message(test_message);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    ASSERT_EQ(ss.str(), test_message);
    reader->terminate();
    queue.destroy();
    reader.destroy();
}


TEST_F(TestSmoggerLibraryFixture, test_complete_logger) {
    smol::singleton<smol::logger> logger;
    logger.init();
    std::stringstream ss;
    std::string test_message = "Test Message {1} {0}";
    std::string formatted = "Test Message 42 string";
    logger->bind_sink("ss", ss);
    smol::jthread jthread([](std::string const& _string) {
        smol::singleton<smol::logger> logger;
        logger->raw(_string, "string", 42);
    }, test_message);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    ASSERT_EQ(ss.str(), formatted);
    logger.destroy();
}

int main(int _argc, char** _argv) {
    ::testing::InitGoogleTest(&_argc, _argv);
    return RUN_ALL_TESTS();
}
