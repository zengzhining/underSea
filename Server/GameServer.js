
var io = require('socket.io')();

function User(id , name)
{
  this.id_ = id;
  this.name_ = name;
}

function AllUser( User1, User2 )
{
  this.player1_ = User1;
  this.player2_ = User2;
}

function onConnect( socket ){
	numOfConnect = numOfConnect + 1;
  socket.emit("connect", "");
  // io.emit('num Connect', numOfConnect.toString());
	// io.emit('num Connect', "Sadi");
};

function onLogin( socket ){

};

function onStart( socket ){
  console.log("onStart~~~~~");
  io.emit('start', "");
}

function onDisConnect( socket ){
	console.log("onDisConnect");
	numOfConnect = numOfConnect - 1;
  var name = socket.userName_;
  if (name == AllUsers[0].name_) {
    AllUsers.splice(0,1);
  }
  else
  {
    AllUsers.splice(1,1);
  }
   console.log(JSON.stringify(AllUsers));
}

function onChat(message){
	io.emit('chat message', message);
}

var numOfConnect = 0;
var AllUsers = new Array();
io.on('connection', function(socket){
  console.log("one connect");
  onConnect(socket);

  socket.on('chat message', function(msg){
    console.log(msg);
    onChat(msg);
  });

  socket.on('upload name', function(msg){
    socket.userName_ = msg;
    var player = new User(numOfConnect , socket.userName_);
    AllUsers.push( player );
    socket.emit('upload name', "");
  });

  socket.on("login", function(msg){
    console.log("on login~~~~");
    //向刚连接的发送全部人数
    console.log(JSON.stringify(AllUsers));
    if (AllUsers.length > 1) {
     socket.emit('all users', JSON.stringify(AllUsers[0]));
     socket.emit('all users', JSON.stringify(AllUsers[1]));
    }
    else
    {
     socket.emit('all users', JSON.stringify(AllUsers[0]));
    }
    //向其他人员广播人数增加
    socket.broadcast.emit('all users', JSON.stringify(AllUsers[1]));
  });

  socket.on("start", function(msg){
    onStart(socket);
  });
  socket.on('disconnect', function () {
  	onDisConnect( socket );
  if (socket.userName_)
  {
  	onChat(socket.userName_.concat(" disconnect"));
  }
  });
});

console.log('listening on *:3211');
io.listen(3211);
