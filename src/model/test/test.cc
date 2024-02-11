#include <gtest/gtest.h>

#include "model/cave_model.h"
#include "model/maze_model.h"

TEST(maze_test, test_load_maze_50x50) {
  mcg::MazeModel m;
  bool ok = m.Load("examples/maze50x50.txt");
  mcg::maze::WallsMap maze = m.GetMap();

  ASSERT_TRUE(ok);
  ASSERT_TRUE(maze.GetCols() == 50);
  ASSERT_TRUE(maze.GetRows() == 50);

  bool solved = m.Solve({0, 0}, {maze.GetRows() - 1, maze.GetCols() - 1});

  ASSERT_TRUE(solved);
}

TEST(maze_test, test_load_maze_5x5) {
  mcg::MazeModel m;
  bool ok = m.Load("examples/maze5x5.txt");
  mcg::maze::WallsMap maze = m.GetMap();

  ASSERT_TRUE(ok);
  ASSERT_TRUE(maze.GetCols() == 5);
  ASSERT_TRUE(maze.GetRows() == 5);

  bool solved = m.Solve({0, 0}, {maze.GetRows() - 1, maze.GetCols() - 1});

  mcg::maze::SolutionMap solution_map = m.GetSolution();

  ASSERT_TRUE(solution_map.GetCols() == 5);
  ASSERT_TRUE(solution_map.GetRows() == 5);

  ASSERT_TRUE(solved);
}

TEST(maze_test, test_save_maze_5x5) {
  mcg::MazeModel m;
  m.Generate(35, 35);
  mcg::maze::WallsMap maze = m.GetMap();

  ASSERT_TRUE(maze.GetCols() == 35);
  ASSERT_TRUE(maze.GetRows() == 35);

  bool saved = m.Save("examples/test_maze.txt");

  ASSERT_TRUE(saved);
}

TEST(maze_test, test_generate_cave_15x15) {
  mcg::CaveModel m;
  const mcg::cave::Params params = {.rows = 25,
                                    .cols = 25,
                                    .life_chance = 40,
                                    .live_limit = {3, 7},
                                    .born_limit = {4, 5}};
  m.Generate(params);
  mcg::cave::WallsMap cave = m.GetMap();

  ASSERT_TRUE(cave.GetCols() == 25);
  ASSERT_TRUE(cave.GetRows() == 25);

  m.GenerateNext(params);

  mcg::cave::WallsMap next_cave = m.GetMap();

  ASSERT_TRUE(cave.GetCols() == 25);
  ASSERT_TRUE(cave.GetRows() == 25);
}

TEST(maze_test, test_load_cave_20x20) {
  mcg::CaveModel m;
  bool ok = m.Load("examples/cave20x20.txt");
  mcg::cave::WallsMap cave = m.GetMap();

  ASSERT_TRUE(ok);
  ASSERT_TRUE(cave.GetCols() == 20);
  ASSERT_TRUE(cave.GetRows() == 20);
}

TEST(maze_test, test_load_cave_10x10) {
  mcg::CaveModel m;
  bool ok = m.Load("examples/cave10x10.txt");
  mcg::cave::WallsMap cave = m.GetMap();

  ASSERT_TRUE(ok);
  ASSERT_TRUE(cave.GetCols() == 10);
  ASSERT_TRUE(cave.GetRows() == 10);
}

TEST(maze_test, test_save_cave_35x35) {
  mcg::CaveModel m;
  m.Generate({.rows = 35,
              .cols = 35,
              .life_chance = 40,
              .live_limit = {3, 7},
              .born_limit = {4, 5}});
  mcg::cave::WallsMap cave = m.GetMap();

  ASSERT_TRUE(cave.GetCols() == 35);
  ASSERT_TRUE(cave.GetRows() == 35);

  bool saved = m.Save("examples/test_cave.txt");

  ASSERT_TRUE(saved);
}

TEST(maze_test, test_generate_cave_4x4) {
  mcg::CaveModel m;
  m.Generate({.rows = 4,
              .cols = 4,
              .life_chance = 60,
              .live_limit = {3, 7},
              .born_limit = {4, 5}});
  mcg::cave::WallsMap cave = m.GetMap();

  ASSERT_TRUE(cave.GetCols() == 4);
  ASSERT_TRUE(cave.GetRows() == 4);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}