var dgram = require('dgram'),
fileSystem = require('fs'),
highScores,
server;


//Load high scores from file
fileSystem.readFile("HighScores.txt", 'utf8', function(err,data){

    if(err){
        //Error occurred loading file, spit out error message then die
        console.log("Error occurred loading file");
        process.exit();
    }

    console.log("Loading high scores from file");

    try{
        // use JSON to turn file contents back into a Javascript array object
        highScores = JSON.parse(data);
    }catch(e)
    {
        // Exception occurred parsing file contents as JSON, error out and die.
        console.log("Exception occured parsing data");
        process.exit();
    }

    // Now sort the high scores by score, high to low
    highScores.Scores.sort(function(a,b){
        return b.Score - a.Score;
    });

    // Display the sorted high scores to the console
    console.log(highScores);
});

//Create a UDP socket
server = dgram.createSocket('udp4');
console.log("Socket created");

// Add a handler for incoming traffic on the socket. This will be called each time something connects to the socket
server.on("message",function (msg,rinfo) {
        //console.log(parseInt(msg).toString());
		console.log(rinfo);

        // SFML sends two packets, one with the size of the following packet ( as a 4 byte number )
        // We don't need it, so as a crude-hack, we ignore any 4 byte packets
        if(rinfo.size != 4)
		{
			console.log("Received message:" + msg.toString());

            // Socket data comes in as a JSON encoded array of objects, turn back into a JS object
            var jsonData,i;

            try{
                jsonData = JSON.parse(msg);
            }
            catch( exception ) {
                console.log("Invalid JSON request received");
                return; // Non lethal error, just stop processing packet
            }

            // The action parameter determines what you should do with this packet
			switch(jsonData.action)
			{
                // action==AddScore, add the score to the highscore array if it's higher than an existing score
                case "AddScore":
					console.log("AddScore called\n");

                    // Make sure highscore has been initialized... order can be a weird thing in node
					if(highScores != undefined){

                        // Loop through current highScores ( which should be sorted )
                        // and insert score if a lower match found
						for(i=0;i < highScores.Scores.length;++i)
						{
							if(highScores.Scores[i].Score < jsonData.score){
                                if(highScores.Scores.length > 7){
                                    highScores.Scores.splice(highScores.Scores.length - 1,1);
                                    console.log("Deleting Last Entry, High Score Board too full");
                                }
								highScores.Scores.splice(i,0,{"Name" : jsonData.name, "Score" : jsonData.score});
								console.log("Inserted highscore by: " + jsonData.name);
								break; // match found, stop looping
							}
						}
					}

                    // Display newly created highscore array
					console.log(highScores.Scores);
				break;

                case "GetScores":
                    console.log("Get Scores called");

                    // Turn highscores back into a JSON encoded string
                    var highScoreAsString = JSON.stringify(highScores);

                    // Create a buffer to hold that string
                    var responseBuffer = new Buffer(highScoreAsString.length);

                    // Write the string to the buffer
                    responseBuffer.write(highScoreAsString);

                    // Send it back to the client, using the addressing information passed in via rinfo
                    server.send(responseBuffer,0,responseBuffer.length,rinfo.port,rinfo.address,
                        function(err, sent){
                            if(err)
                                console.log("Error sending response");
                            else
                                console.log("Responded to client at  " + rinfo.address + ":" + rinfo.port );

                        });
                break;
			}

		}
		//
		//
});

// Called when socket starts listening for packets. besides logging, currently serves no purpose
server.on("listening", function () {
    var address = server.address();
    console.log("server listening " +
        address.address + ":" + address.port);
});

// Finally, bind the server to port 1000.  1000 was randomly chosen.  Think of this as saying GO!
// Now we are listening for UDP connections on port 1000
server.bind(1000);
