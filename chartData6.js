$(document).ready(function(){
    $.ajax({
        //async:false,
        url: "https://gggguj.000webhostapp.com/batteryGET.php",
        method: "GET",
        success: function(data) {
            //console.log(data);
            var player = [];
            var bat_percentage = [];
            var bat_volt = [];
            var bat_current = [];
            var timeLeft = [];

            for(var i in data) {
                player.push(data[i].id);
                bat_percentage.push(data[i].value7);
                bat_volt.push(data[i].value8);
                bat_current.push(data[i].value9);
                timeLeft.push(data[i].value10);
            }

            // console.log(player);
            // console.log(bat_percentage);
            $("#timeLeft").append(" " + timeLeft[0]); 
            $("#currentPercentage").append(" " + bat_percentage[0]); 
            $("#currentVolt").append(" " + bat_volt[0]); 
            $("#currentAmp").append(" " + bat_current[0]); 

            //fetch data starts from DESC 
            var playerRev = player.reverse();
            var percentageRev = bat_percentage.reverse();

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
                        borderColor: "rgba(242,175,62,1)",
                        pointBackgroundColor: "rgba(242,175,62,1)",
                        pointBorderColor: "#fff",
                        pointHoverBackgroundColor: "#fff",
                        pointHoverBorderColor: "rgba(242,175,62,1)",

                        borderWidth: 2, //kecik sikit 2
                        pointRadius: 0,
                        data: percentageRev
                    }
                ]
            };
			
            var ctx = $("#myChart6");

            var barGraph = new Chart(ctx, {
                type: 'line',
                data: chartdata,

                options: {
                    title: {
                        display: true,
                        text: 'Battery Percentage (in %)' 
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
                                max: 200,
                                min: 1,
                                stepSize: 100,
                                display: false
                            }

							

                        }],

                        yAxes: [{
					
                            ticks: {
                                max: 100,
                                min: 0,
                                stepSize: 50
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