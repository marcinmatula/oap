/*
 * Copyright 2016 - 2019 Marcin Matula
 *
 * This file is part of Oap.
 *
 * Oap is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Oap is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Oap.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <map>
#include <csignal>
#include <string>
#include <thread>
#include <functional>

#include "Routine.h"
#include "PatternsClassification.h"

using Factory = std::function<oap::Routine*()>;

const char* g_routinesNameArg = "name";

template<typename UnaryPredicate>
std::vector<char*> copyArgsIf (char** argv, int argc, UnaryPredicate predicate)
{
  std::vector<char*> vec;

  for (int idx = 0; idx < argc; ++idx)
  {
    if (predicate (argv[idx]))
    {
      const size_t len = strlen(argv[idx]);
      char* narg = new char[len + 1];
      strcpy (narg, argv[idx]);
      narg[len] = '\0';
      vec.push_back (narg);
    }
    else
    {
      ++idx; // in the case of skipping some argument we must also skip its value (for example: --name (idx = 1) some_name(idx = 2))
    }
  }

  return vec;
}

void deleteArgv (std::vector<char*>& argv)
{
  for (size_t idx = 0; idx < argv.size(); ++idx)
  {
    delete[] argv[idx];
  }
  argv.clear();
}

int main(int argc, char** argv)
{
  using namespace std::placeholders;

  using RoutinesMap = std::map<std::string, Factory>;
  RoutinesMap routines;

  routines["patterns_classification"] = []() -> oap::Routine* { return new oap::PatternsClassification (); };

  auto getNamesList = [](const RoutinesMap& routines) -> std::string
  {
    std::vector<std::string> list;
    std::string listStr;
    for (auto it = routines.cbegin(); it != routines.cend(); ++it)
    {
      list.push_back (it->first);
    }

    for (size_t idx = 0; idx < list.size(); ++idx)
    {
      listStr += list[idx];
      if (idx < list.size() - 1)
      {
        listStr += ", ";
      }
    }
    return listStr;
  };

  auto nameCallback = [&routines, &getNamesList, argc, argv](const std::string& value)
  {
    auto it = routines.find (value);
    if (it == routines.end ())
    {
      std::stringstream sstream;
      sstream << "Routine \"" << value << "\" doesn\'t exist. Routines: ";
      sstream << getNamesList (routines) << '.';
      throw std::runtime_error (sstream.str ());
    }

    std::unique_ptr<oap::Routine> routine (it->second());

    auto pred = [] (const std::string& arg)
    {
      return !(arg == "--" + std::string(g_routinesNameArg));
    };
    std::vector<char*> nargv = std::move (copyArgsIf (argv, argc, pred));

    auto thread = std::thread([&routine, &value, nargv]()
    {
      char* const* argv = nargv.data();
      const size_t nargc = nargv.size();
      int status = routine->run (nargc, argv);
      if (status != 0)
      {
        logError ("Routine %s exit with %d", value.c_str(), status);
      }
    });

    thread.join ();
    deleteArgv (nargv);
  };

  oap::ArgsParser argParser;
  argParser.registerArg (g_routinesNameArg, nameCallback);

  try
  {
    argParser.parse (argc, argv);
  }
  catch (const std::exception& exception)
  {
    logError ("%s", exception.what ());
    return 1;
  }

  return 0;
}
