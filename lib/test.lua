-- Copyright 2022 Kai D. Gonzalez
-- 
-- Licensed under the Apache License, Version 2.0 (the "License");
-- you may not use this file except in compliance with the License.
-- You may obtain a copy of the License at
-- 
--     http://www.apache.org/licenses/LICENSE-2.0
-- 
-- Unless required by applicable law or agreed to in writing, software
-- distributed under the License is distributed on an "AS IS" BASIS,
-- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
-- See the License for the specific language governing permissions and
-- limitations under the License.

local krux = require("krux")

-- Make a folder called "hello" and add "test.txt" to it.

krux.mkdir("hello")

local file = io.open("hello/test.txt", "w")

file:write("hello!")

file:close()

-- Confirm if "hello" was made.

assert(krux.exists("hello"))

print("hello.txt is there!")

-- Sleep

krux.sleep(4)

-- Remove "hello/test.txt"

krux.rm("hello/test.txt")

-- Add a file and delete hello/ using the RemoveAll function.

local file = io.open("hello/remove_this_directory.txt", "w")

file:write("hello!")

file:close()

krux.rmall("hello/")

if krux.usingrl ~= nil then
    print("Type anything into the box (krux.read)")
    local input = krux.read("> ")
    print("Here's your input: " .. input)

    krux.sleep(1)

    print("I've added it to your history, try typing UP-ARROW this time.")
    
    -- Add it to history
    krux.addhistory(input)

    -- Send another read prompt - discard value!
    krux.read("> ")
end