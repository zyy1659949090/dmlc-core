// Copyright by Contributors
#include <dmlc/config.h>
#include <gtest/gtest.h>
#include <dmlc/parameter.h>

TEST(Env, Blank) {
  const char *var_name = "test_environment_var__askjaposcjp";
  ::setenv(var_name, "foo", 1);
  std::string res = dmlc::GetEnv(var_name, std::string("not_food"));
  GTEST_ASSERT_EQ(res, "foo");
  ::setenv(var_name, "bar", 1);
  res = dmlc::GetEnv(var_name, std::string("bar"));
  GTEST_ASSERT_EQ(res, "bar");
  ::putenv(const_cast<char *>((std::string() + var_name + "=").c_str()));
  const char *s = ::getenv(var_name);  // On Mac, this may return an empty string
  if (s) {
    // Some implementations will return an empty string instead of null
    res = dmlc::GetEnv(var_name, std::string("another_default"));
    GTEST_ASSERT_EQ(res, "another_default");
  }
  ::setenv(var_name, "", 1);
  s = ::getenv(var_name);  // On Linux, this may return an empty string
  if (s) {
    // Some implementations will return an empty string instead of null
    res = dmlc::GetEnv(var_name, std::string("another_default"));
    GTEST_ASSERT_EQ(res, "another_default");
  }
}
