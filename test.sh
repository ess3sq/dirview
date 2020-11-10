# This shell script creates the following directory
# # tree structure for testing purposesL

# test
#     test/a
#         test/a/aa
#         test/a/ab
#             test/a/ab/aba
#     test/b
#         test/b/test.da
#     test/.hidden_dir
#         test/.hidden_dir/file
#     test/.hidden_file

mkdir test test/a test/a/aa test/a/ab test/a/ab/aba test/b test/.hidden_dir
touch test/b/test.da test/.hidden_dir/file test/.hidden_file