[source]
../../smtest/plugin/smtest.sp
../scripting/l4d2util.sp
src/botspawner.sp
src/rounds.sp

[includes]
../scripting/include
../scripting
../../smtest/plugin/include

[commands]
map c5m1_waterfront
wait 20
spawn_bots
wait 1
sm_test_run
wait 25
sm_test_output
