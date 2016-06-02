print('bootstrap script working...');
function writeFile(filename,content)
file.open(filename,"w")
file.write(content)
file.close()
end
local file_list = {}
m=mqtt.Client('bootstrap'..node.chipid())
function next_file()
  if #file_list == 0 then
    m:close();
    print('\035initialized')
    return
  end
  m:subscribe("/bootstrap/file/"..table.remove(file_list,#file_list), 2)
end
m:on("message",function(conn,topic,data)
  print(topic)
  if topic=="/bootstrap/list" then
    for i in string.gmatch(data, "[^\n\r]+") do
      table.insert(file_list,i)
    end
    next_file()
    return
  end
  local fn = topic:match("/bootstrap/file/(.+)")
  if fn and data~=nil then
    writeFile(fn, data)
  end
  next_file()
end)
-- _,_,gw=wifi.sta.getip()
gw='tdxls-iot.xicp.net'
m:connect(gw, 1883, 0, function(conn) 
  m:subscribe("/bootstrap/list", 2)
end)

bootstrap.lua
comm.lua
comm2.lua
init.lua
parser.lua
print('bootstrap script working...');
function writeFile(filename,content)
file.open(filename,"w")
file.write(content)
file.close()
end
local file_list = {}
m=mqtt.Client('bootstrap'..node.chipid())
function next_file()
  if #file_list == 0 then
    m:close();
    print('\035initialized')
    return
  end
  m:subscribe("/bootstrap/file/"..table.remove(file_list,#file_list), 2)
end
m:on("message",function(conn,topic,data)
  print(topic)
  if topic=="/bootstrap/list" then
    for i in string.gmatch(data, "[^\n\r]+") do
      table.insert(file_list,i)
    end
    next_file()
    return
  end
  local fn = topic:match("/bootstrap/file/(.+)")
  if fn and data~=nil then
    writeFile(fn, data)
  end
  next_file()
end)
-- _,_,gw=wifi.sta.getip()
gw='tdxls-iot.xicp.net'
m:connect(gw, 1883, 0, function(conn) 
  m:subscribe("/bootstrap/list", 2)
end)

local M = {}

function M.connect( server, port )
	M.m:connect(server, port, 0) -- 1 for secure
end
function M.publish(cate, key, value, qos, retain)
	M.m:publish("/"..cate.."/"..M.name.."/"..key,value,qos,retain)
end
function M.subscribe( topic, qos )
	M.m:subscribe(topic,qos, function(conn) print("#subscribed") end)
end
function M.multi_subscribe(topic)
	M.m:subscribe(topic, function(conn) print("#multi-subscribed") end)
end
function M.close( )
	M.m:close();
end

local comm2 = require('comm2')
setmetatable(M, {__index = comm2})

return M
local M = {}

function M.init( name )
    M.m = mqtt.Client()
    M.parser = require 'parser'
    M.name = name
    M.m:lwt("/events/"..name.."/offline", "", 2, 0)
    M.m:on("connect", function(con)
        print ("#connected")
        M.m:subscribe("/control/"..M.name.."/+",2)
    end)
    M.m:on("offline", function(con) print ("#offline") end)

    M.m:on("message", function(conn, topic, data) 
        M.parser.parse(M.name, topic, data)
    end)
end
return M

print("#started")
local parser = {}

function parser.parse(name,topic,data)
	print(topic)
	if topic:find("^/control/")then
		local tok = topic:match("^/control/.+/(.+)")
		if tok then
			print("#control+"..tok.."+"..data)
		end
	end
end

return parser
