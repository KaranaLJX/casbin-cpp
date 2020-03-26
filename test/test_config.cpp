#include <direct.h>

#include "pch.h"
#include "../casbin/config/Config.h"

using namespace std;

class TestConfig : public ::testing::Test {
	protected:

		void SetUp() override {
			char* root = _getcwd(NULL, 0);
			string filepath = string(root) + "/../../casbin/config/testdata/testini.ini";
			config = Config::newConfig(filepath);
		}

		Config config;
};

TEST_F(TestConfig, TestDebug) {
	EXPECT_TRUE(config.getBool("debug"));
}

TEST_F(TestConfig, TestURL) {
	EXPECT_EQ( "act.wiki", config.getString("url"));
}

TEST_F(TestConfig, TestRedis) {
	vector <string> values = config.getStrings("redis::redis.key");
	EXPECT_EQ("push1", values[0]);
	EXPECT_EQ("push2", values[1]);
}

TEST_F(TestConfig, TestMYSQLDEV) {
	EXPECT_EQ("127.0.0.1", config.getString("mysql::mysql.dev.host"));
}

TEST_F(TestConfig, TestMYSQLMASTER) {
	EXPECT_EQ("10.0.0.1", config.getString("mysql::mysql.master.host"));
}

TEST_F(TestConfig, TestMathInt) {
	EXPECT_EQ(64, config.getInt("math::math.i64"));
}

TEST_F(TestConfig, TestMathFloat) {
	EXPECT_EQ(float(64.1), config.getFloat("math::math.f64"));
}

TEST_F(TestConfig, TestSetConfig) {
	config.set("other::key1", "new test key");
	EXPECT_EQ("new test key", config.getString("other::key1"));
}

TEST_F(TestConfig, TestMulti) {
	EXPECT_EQ("r.sub==p.sub && r.obj==p.obj", config.getString("multi1::name"));
}