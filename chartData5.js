$(document).ready(function(){
    $.ajax({
        //async:false,
        url: "https://gggguj.000webhostapp.com/actionGET.php",
        method: "GET",
        success: function(data) {
            //console.log(data);
            var player = [];
            var score = [];

            for(var i in data) {
                player.push(data[i].id);
                score.push(data[i].value15);
            }

            // console.log(player);
            // console.log(score);

            var player_rev = player.reverse();
            var score_rev = score.reverse();

            var chartdata = {
                labels: player_rev,
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
                        data: score_rev
                    }
                ]
            };
			
            var ctx = $("#myChart5");

            var barGraph = new Chart(ctx, {
                type: 'line',
                data: chartdata,

                options: {
                    title: {
                        display: true,
                        text: 'Z-value (in Degree)' 
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
                                max: 180,
                                min: -180,
                                stepSize: 90
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