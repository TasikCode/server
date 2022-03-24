#
# suite.pm will make sure that all tests including this file
# will be skipped unless innodb is enabled
#
--disable_query_log
if (`select count(*) from information_schema.system_variables where variable_name='have_sanitizer' and global_value like "MSAN%"`)
{
if (`select @@sql_log_bin=0`)
{
call mtr.add_suppression("InnoDB: Trying to delete tablespace.*pending operations");
}
if (`select @@sql_log_bin`)
{
set @@sql_log_bin=0;
call mtr.add_suppression("InnoDB: Trying to delete tablespace.*pending operations");
set @@sql_log_bin=1;
}
}
if ($VALGRIND_TEST)
{
if (`select @@sql_log_bin=0`)
{
call mtr.add_suppression("InnoDB: Trying to delete tablespace.*pending operations");
}
if (`select @@sql_log_bin`)
{
set @@sql_log_bin=0;
call mtr.add_suppression("InnoDB: Trying to delete tablespace.*pending operations");
set @@sql_log_bin=1;
}
}
--enable_query_log
