#include "gtest/gtest.h"

#include "../src/header/Base.h"
#include "../src/header/Command.h"
#include "../src/header/Connector.h"
#include "../src/header/Shell.h"
#include "../src/header/And.h"
#include "../src/header/Or.h"
#include "../src/header/Semicolon.h"
#include "../src/header/Command_mock.h"
#include "../src/header/My_In.h"
#include "../src/header/My_Out.h"
#include "../src/header/My_Out_Append.h"
#include "../src/header/My_Pipe.h"


#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

TEST(Parse_test, Parse) 
{	
	Shell my_shell;
	my_shell.set_input("ls -a; echo \"hello && echo hi\" || exti");
	my_shell.parse();
	EXPECT_EQ (my_shell.get_my_vec(0), "ls");
	EXPECT_EQ (my_shell.get_my_vec(1), "-a");
	EXPECT_EQ (my_shell.get_my_vec(4), "hello && echo hi");
	EXPECT_EQ (my_shell.get_my_vec(5), "||");
	EXPECT_EQ (my_shell.get_my_vec(2), ";");
}

TEST(Connectors_test, And_false)
{
        Base* left = new Command_mock(false);
	Base* right = new Command_mock(true);
	Base* exec = new And(left, right);
	exec->execute(0, 1);
	EXPECT_EQ (exec->result, "false");
}

TEST(Connectors_test, And_false2)
{
        Base* left = new Command_mock(true);
        Base* right = new Command_mock(false);
        Base* exec = new And(left, right);
        exec->execute(0, 1);
        EXPECT_EQ (exec->result, "false");
}

TEST(Connectors_test, And_true)
{
    Base* left = new Command_mock(true);
    Base* right = new Command_mock(true);
    Base* exec = new And(left, right);
    exec->execute(0, 1);
    EXPECT_EQ (exec->result, "true");	
}

TEST(Connectors_test, Or_true)
{
    Base* left = new Command_mock(true);
    Base* right = new Command_mock(false);
    Base* exec = new Or(left, right);
    exec->execute(0, 1);
    EXPECT_EQ (exec->result, "true");
}

TEST(Connectors_test, Or_true2)
{
    Base* left = new Command_mock(false);
    Base* right = new Command_mock(true);
    Base* exec = new Or(left, right);
    exec->execute(0, 1);
    EXPECT_EQ (exec->result, "true");
}

TEST(Connectors_test, Or_false)
{
    Base* left = new Command_mock(false);
    Base* right = new Command_mock(false);
    Base* exec = new Or(left, right);
    exec->execute(0, 1);
    EXPECT_EQ (exec->result, "false");
}

TEST(Connectors_test, Semi_true)
{
    Base* left = new Command_mock(false);
    Base* right = new Command_mock(true);
    Base* exec = new Semicolon(left, right);
    exec->execute(0, 1);
    EXPECT_EQ (exec->result, "true");
}


TEST(TestCommand_test, test_e)
{
	vector<string> argv = {"test", "-e", "src/"};
	Command* cmd = new Command(argv);
	cmd->execute(0, 1);
	EXPECT_EQ (true, cmd->exec_flag);
}

TEST(TestCommand_test, test_e_f)
{
        vector<string> argv = {"test", "-e", "abc/"};
        Command* cmd = new Command(argv);
        cmd->execute(0, 1);
        EXPECT_EQ (false, cmd->exec_flag);
}

TEST(TestCommand_test, test_d)
{
        vector<string> argv = {"test", "-d", "src/"};
        Command* cmd = new Command(argv);
        cmd->execute(0, 1);
        EXPECT_EQ (true, cmd->exec_flag);
}

TEST(TestCommand_test, test_d_f)
{
        vector<string> argv = {"test", "-d", "README.md"};
        Command* cmd = new Command(argv);
        cmd->execute(0, 1);
        EXPECT_EQ (false, cmd->exec_flag);
}

TEST(TestCommand_test, test_f)
{
        vector<string> argv = {"test", "-f", "src/"};
        Command* cmd = new Command(argv);
        cmd->execute(0, 1);
        EXPECT_EQ (false, cmd->exec_flag);
}

TEST(Redirection, input_output)
{
	vector<string> com1 = {"cat"};
	vector<string> com2 = {"in.txt"};
	vector<string> com3 = {"out.txt"};
	Base* left = new Command(com1);
	Base* right = new Command(com2);
	Base* in_red = new My_In(left, right);
	right = new Command(com3);
	Base* out_red = new My_Out(in_red, right);
	out_red->execute(0, 1);
	EXPECT_EQ(out_red->read_file("in.txt"), out_red->read_file("out.txt"));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
