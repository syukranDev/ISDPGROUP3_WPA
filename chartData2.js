$(document).ready(function(){
    $.ajax({
        //async:false,
        url: "https://gggguj.000webhostapp.com/tempGET.php",
        method: "GET",
        success: function(data) {
            //console.log(data);
            var player = [];
            var score = [];

            for(var i in data) {
                player.push(data[i].id);
                score.push(data[i].value1);
            }

            // console.log(player);
            // console.log(score);

            var temp_Min = Math.min(...score);
            var temp_Max = Math.max(...score);
            var temp_Current = score[0];
            
            // console.log(bpm_Max);
            // console.log(bpm_Min);
            // console.log(bpm_Current);
            $("#minTemp").append(" " + temp_Min);
            $("#maxTemp").append(" " + temp_Max);
            $("#currentTemp").append(" " + temp_Current);
            $("#currentTemp2").append(" " + temp_Current); //copy from above line as ID is unique

            //fetch data starts from DESC 
            var playerRev = player.reverse();
            var scoreRev = score.reverse();
            
            var chartdata = {
                labels: playerRev,
                datasets: [
                    {
                        //fill: true,
                        //backgroundColor: '#c31432',
                        //rgb(54, 162, 235)
                        // backgroundColor: ['rgba(54, 162, 235, 0.3)', 'rgba(0,187,122,0.3)', 'rgba(254,176,25,0.3)'],
                        // borderColor: ['rgb(54, 162, 235)', 'rgb(0,187,122)', 'rgb(254,176,25)'],
                        backgroundColor: "rgba(255,255,255,0)",
                        borderColor: "rgba(82,185,159,1)",
                        pointBackgroundColor: "rgba(82,185,159,1)",
                        pointBorderColor: "#fff",
                        pointHoverBackgroundColor: "#fff",
                        pointHoverBorderColor: "rgba(82,185,159,1)",

                        //borderWidth: 2,
                        pointRadius: 0,
                        data: scoreRev
                    }
                ]
            };
			
            var ctx = $("#myChart");

            var barGraph = new Chart(ctx, {
                type: 'line',
                data: chartdata,

                options: {
                    title: {
                        display: true,
                        text: 'Temperature (in Celcius)' 
                    },

                    legend: {
                        display: false,
						
                    },
                    scales: {
                        xAxes: [{
                            gridLines: {
                                display: false
                            },

                            ticks: {
                                max: 175,
                                min: 1,
                                stepSize: 50,
                                display: false
                            }

							

                        }],

                        yAxes: [{
					
                            ticks: {
                                max: 40,
                                min: 28,
                                stepSize: 2
                            },

                            gridLines: {
                                // display: false
                            }
                        }]
                    }
                },


            });

            // setInterval(function(){
            //     $.ajax();
            //     }, 10000);
			
            
        }
    });
});



