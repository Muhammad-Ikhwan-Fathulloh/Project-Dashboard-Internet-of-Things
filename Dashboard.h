char webpage[] PROGMEM = R"=====(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="Mark Otto, Jacob Thornton, and Bootstrap contributors">
    <meta name="generator" content="Hugo 0.84.0">
    <title>Smart Aquarium System</title>

    <link rel="canonical" href="https://getbootstrap.com/docs/5.0/examples/album/">

    <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.3.0/css/font-awesome.min.css" rel="stylesheet">

    <!-- Bootstrap core CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">

    <!-- Favicons -->
    <meta name="theme-color" content="#7952b3">

    <link rel="icon" href="https://i.ibb.co/n7HKTsK/Smart-Aquarium.png" sizes="32x32" type="image/png">
    <link rel="icon" href="https://i.ibb.co/n7HKTsK/Smart-Aquarium.png" sizes="16x16" type="image/png">


    <style>
        @import url('https://fonts.googleapis.com/css2?family=Fredoka+One&display=swap');
  .times{
    display: inline;
    margin: 5px;
  }

  #time{
    font-size: 60px;
    color: #004AAD;
  }

  #day{
    font-size: 40px;
    color: #FF5757;
  }

  #date{
    font-size:20px;
    color: #FF5757;
  }
  .timex{
    font-family: 'Fredoka One', cursive;
  }

      .bd-placeholder-img {
        font-size: 1.125rem;
        text-anchor: middle;
        -webkit-user-select: none;
        -moz-user-select: none;
        user-select: none;
      }

      @media (min-width: 768px) {
        .bd-placeholder-img-lg {
          font-size: 3.5rem
        }
      }

      .card {
        background-color: #fff;
        border-radius: 10px;
        border: none;
        position: relative;
        margin-bottom: 30px;
        box-shadow: 0 0.46875rem 2.1875rem rgba(90,97,105,0.1), 0 0.9375rem 1.40625rem rgba(90,97,105,0.1), 0 0.25rem 0.53125rem rgba(90,97,105,0.12), 0 0.125rem 0.1875rem rgba(90,97,105,0.1);
    }
    .l-bg-cherry {
        background: linear-gradient(to right, #493240, #f09) !important;
        color: #fff;
    }
    
    .l-bg-blue-dark {
        background: linear-gradient(to right, #373b44, #4286f4) !important;
        color: #fff;
    }
    
    .l-bg-green-dark {
        background: linear-gradient(to right, #0a504a, #38ef7d) !important;
        color: #fff;
    }
    
    .l-bg-orange-dark {
        background: linear-gradient(to right, #a86008, #ffba56) !important;
        color: #fff;
    }
    
    .card .card-statistic-3 .card-icon-large .fas, .card .card-statistic-3 .card-icon-large .far, .card .card-statistic-3 .card-icon-large .fab, .card .card-statistic-3 .card-icon-large .fal {
        font-size: 110px;
    }
    
    .card .card-statistic-3 .card-icon {
        text-align: center;
        line-height: 50px;
        margin-left: 15px;
        color: #000;
        position: absolute;
        right: -5px;
        top: 20px;
        opacity: 0.1;
    }
    
    .bg-c-blue {
        background: linear-gradient(45deg,#4099ff,#73b4ff);
    }
    
    .bg-c-green {
        background: linear-gradient(45deg,#2ed8b6,#59e0c5);
    }
    
    .bg-c-yellow {
        background: linear-gradient(45deg,#FFB64D,#ffcb80);
    }
    
    .bg-c-pink {
        background: linear-gradient(45deg,#FF5370,#ff869a);
    }
    
    </style>

    
  </head>
  <body>
    <script type="text/javascript">
        var connection = new WebSocket('ws://'+location.hostname+':81/')
        var button_1_status = 0
        var button_2_status = 0
        var button_3_status = 0
        var button_4_status = 0
        var button_light_status = 0
        var title = 0;
        var counter = 0;

        connection.onmessage = function(event){
          var full_data = event.data
          console.log(full_data)
          var data = JSON.parse(full_data)

          title = data.title
          counter = data.counter
          
          document.getElementById("title_value").innerHTML = title
          document.getElementById("counter_value").innerHTML = counter
        }

        

        function webcam_on()
        {
          document.getElementById("webcamon").setAttribute("class", "text-white btn bg-c-green")
          document.getElementById("webcamoff").setAttribute("class", "text-danger btn btn-outline-danger")
          

          if (localStorage.getItem("input_webcam") == null) {
            document.getElementById("webcam").innerHTML = `<div class="col-sm-4 mt-3">
              <div class="card border-dark" style="height: 20rem">
                <div class="card-body">
                  <h5 class="card-title"><i class="fa fa-camera f-left"></i> Webcam</h5>
                  <strong>Input Webcam Link !!!</strong>
                </div>
              </div>
            </div>` 
          }else{
            local_webcam = localStorage.getItem("input_webcam")
            document.getElementById("webcam").innerHTML = `<div class="col-sm-4 mt-3">
              <div class="card border-dark" style="height: 20rem">
                <div class="card-body">
                  <h5 class="card-title"><i class="fa fa-camera f-left"></i> Webcam</h5>
                  <iframe style="display:auto;" width="400" height="300"
                  src="${local_webcam}" allowfullscreen>
                  </iframe>
                </div>
              </div>
            </div>` 
          }
          
        }

        function webcam_off()
        {
          document.getElementById("webcamon").setAttribute("class", "text-success btn btn-outline-success")
          document.getElementById("webcamoff").setAttribute("class", "text-white btn bg-c-pink")
          document.getElementById("webcam").innerHTML = `` 
        }

        function webcam_light_on()
        {
            document.getElementById("webcam_lighton").setAttribute("class", "text-white btn bg-c-green")
            document.getElementById("webcam_lightoff").setAttribute("class", "text-danger btn btn-outline-danger")
            button_light_status = 1 
            console.log("Webcam light is ON")
            send_data()
        }
        function webcam_light_off()
        {
            document.getElementById("webcam_lighton").setAttribute("class", "text-success btn btn-outline-success")
            document.getElementById("webcam_lightoff").setAttribute("class", "text-white btn bg-c-pink")
            button_light_status = 0
            console.log("Webcam light is OFF")
            send_data()
        }
    
        function button_1_on()
        {
            document.getElementById("button_1on").setAttribute("class", "text-white btn bg-c-green")
            document.getElementById("button_1off").setAttribute("class", "text-danger btn btn-outline-danger")
            button_1_status = 1 
            console.log("Kontak 1 is ON")
            send_data()
        }
        function button_1_off()
        {
            document.getElementById("button_1on").setAttribute("class", "text-success btn btn-outline-success")
            document.getElementById("button_1off").setAttribute("class", "text-white btn bg-c-pink")
            button_1_status = 0
            console.log("Kontak 1 is OFF")
            send_data()
        }

        function button_2_on()
        {
            document.getElementById("button_2on").setAttribute("class", "text-white btn bg-c-green")
            document.getElementById("button_2off").setAttribute("class", "text-danger btn btn-outline-danger")
            button_2_status = 1 
            console.log("Kontak 2 is ON")
            send_data()
        }
        function button_2_off()
        {
            document.getElementById("button_2on").setAttribute("class", "text-success btn btn-outline-success")
            document.getElementById("button_2off").setAttribute("class", "text-white btn bg-c-pink")
            button_2_status = 0
            console.log("Kontak 2 is OFF")
            send_data()
        }

        function button_3_on()
        {
            document.getElementById("button_3on").setAttribute("class", "text-white btn bg-c-green")
            document.getElementById("button_3off").setAttribute("class", "text-danger btn btn-outline-danger")
            button_3_status = 1 
            console.log("Kontak 3 is ON")
            send_data()
        }
        function button_3_off()
        {
            document.getElementById("button_3on").setAttribute("class", "text-success btn btn-outline-success")
            document.getElementById("button_3off").setAttribute("class", "text-white btn bg-c-pink")
            button_3_status = 0
            console.log("Kontak 3 is OFF")
            send_data()
        }

        function button_4_on()
        {
            document.getElementById("button_4on").setAttribute("class", "text-white btn bg-c-green")
            document.getElementById("button_4off").setAttribute("class", "text-danger btn btn-outline-danger")
            button_4_status = 1 
            console.log("Kontak 4 is ON")
            send_data()
        }
        function button_4_off()
        {
            document.getElementById("button_4on").setAttribute("class", "text-success btn btn-outline-success")
            document.getElementById("button_4off").setAttribute("class", "text-white btn bg-c-pink")
            button_4_status = 0
            console.log("Kontak 4 is OFF")
            send_data()
        }

        function send_data()
        {
          var full_data = '{"Kontak1" :'+button_1_status+',"Kontak2":'+button_2_status+',"Kontak3":'+button_3_status+',"Kontak4":'+button_4_status+',"webcam_light":'+button_light_status+'}'
          connection.send(full_data)
        }

    </script>
<header>
  <div class="collapse bg-dark" id="navbarHeader">
    <div class="container">
      <div class="row">
        <div class="col-sm-8 col-md-7 py-4">
          <h4 class="text-white">About</h4>
          <p class="text-muted">Smart Aquarium System is an aquarium monitoring system using a live streaming camera, and can control systems such as automatic feeding, lighting, pumps, and water purifiers with a website-based Internet of Things.</p>
        </div>
        <div class="col-sm-4 offset-md-1 py-4">
          <!-- <h4 class="text-white">Contact</h4>
          <ul class="list-unstyled">
            <li><a href="https://www.havo.co.id/" class="text-white">Website</a></li>
            <li><a href="https://www.youtube.com/teknologipintar" class="text-white">Youtube</a></li>
            <li><a href="https://www.instagram.com/pintarteknik/" class="text-white">Instagram</a></li>
          </ul> -->
        </div>
      </div>
    </div>
  </div>
  <div class="navbar navbar-dark l-bg-blue-dark shadow-sm">
    <div class="container">
      <a href="#" class="navbar-brand d-flex align-items-center">
        <img src="https://i.ibb.co/h9WTgjV/Smart-Aquarium-Putih.png" alt="" width="50"><strong>Smart Aquarium System</strong>
      </a>
      <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarHeader" aria-controls="navbarHeader" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
      </button>
    </div>
  </div>
</header>

<main>

  <section class="container">
    <div class="row">
        <div class="col-sm-6 mt-5" align="center">
            <img src="https://i.ibb.co/ns5xc32/aquarium.png" class="img-fluid" alt="">
        </div>
      <div class="col mt-5">
        <h1 class="fw-light"><img src="https://i.ibb.co/n7HKTsK/Smart-Aquarium.png" class="img-fluid" width="70" alt=""><strong>Smart Aquarium System</strong></h1>
        <p class="lead text-muted"><i class="fa fa-rss f-left"></i> Controlling and Monitoring System</p>
        <p>
          <a href="https://www.havo.co.id/" class="btn bg-c-yellow my-2 text-white"><strong>Developer</strong></a>
          <a href="/update" class="btn bg-c-blue my-2 text-white"><strong>OTA</strong></a>
        </p>
        <div class="timex">
    
            <p class="times" id="time">1:20PM</p>
            <p class="times" id="day">SUN</p>
            <p class="times" id="date">1 May 2022</p>
    
        </div>
      </div>
    </div>
  </section>


  <div class="container">
    <div class="row justify-content-center" align="center">
      <div class="col mt-3">
          <div class="card border-dark">
              <div class="card-body">
                <h5 class="card-title"><i class="fa fa-cog f-left"></i> Configuration Webcam</h5>
                <div class="row justify-content-center" align="center">
                  <div class="col-sm-4">
                    <label for="exampleFormControlInput1" class="form-label"><strong>Webcam Link</strong></label>
                    <div class="input-group">
                      <input type="input_webcam" class="form-control" id="input_webcam" placeholder="Input Webcam Link">
                    <button class="btn btn-primary" type="button" id="button_webcam"><strong>Save</strong></button>
                    </div>
                    
                  </div>
                </div>
                  <div class="row">
                    <div class="col m-3">
                        <strong> Webcam Status </strong>
                        <br>
                        <div class="btn-group text-white" role="group" aria-label="Basic example">
                            <button id="webcamon" type="button" class="btn btn-outline-success" onclick="webcam_on()" style="width: 5rem"><strong><i class="fa fa-bolt f-left"></i></strong></button> 
                            <button id="webcamoff" type="button" class="btn btn-outline-danger" onclick="webcam_off()" style="width: 5rem"><strong><i class="fa fa-power-off f-left"></i></strong></button>
                        </div>    
                    </div>
                  
                    <div class="col m-3">
                      <strong> Webcam Lighting </strong>
                      <br>
                      <div class="btn-group text-white" role="group" aria-label="Basic example">
                          <button id="webcam_lighton" type="button" class="btn btn-outline-success" onclick="webcam_light_on()" style="width: 5rem"><strong><i class="fa fa-bolt f-left"></i></strong></button> 
                          <button id="webcam_lightoff" type="button" class="btn btn-outline-danger" onclick="webcam_light_off()" style="width: 5rem"><strong><i class="fa fa-power-off f-left"></i></strong></button>
                      </div>    
                  </div>
                  </div>
                 
              </div>
            </div>
      </div>
    </div>
    <div class="row justify-content-center" align="center">
        <div id="webcam"></div>

        <div class="col mt-3">
          <div class="card border-dark">
            <div class="card-body">
                <h5 class="card-title"><i class="fa fa-plug f-left"></i> Controlling</h5>
                <div class="row">
                    <div class="col m-3">
                        <strong> Feeder </strong><br>
                        <div class="btn-group text-white" role="group" aria-label="Basic example">
                            <button id="button_1on" type="button" class="btn btn-outline-success" onclick="button_1_on()" style="width: 5rem"><strong><i class="fa fa-bolt f-left"></i></strong></button> 
                            <button id="button_1off" type="button" class="btn btn-outline-danger" onclick="button_1_off()" style="width: 5rem"><strong><i class="fa fa-power-off f-left"></i></strong></button>
                        </div>    
                    </div>
                    <div class="col m-3">
                        <strong> Lamp </strong><br>
                        <div class="btn-group text-white" role="group" aria-label="Basic example">
                            <button id="button_2on" type="button" class="btn btn-outline-success" onclick="button_2_on()" style="width: 5rem"><strong><i class="fa fa-bolt f-left"></i></strong></button> 
                            <button id="button_2off" type="button" class="btn btn-outline-danger" onclick="button_2_off()" style="width: 5rem"><strong><i class="fa fa-power-off f-left"></i></strong></button>
                        </div>
                    </div>            
                </div>
                <div class="row">
                    <div class="col m-3">
                        <strong> Pump </strong><br>
                        <div class="btn-group text-white" role="group" aria-label="Basic example">
                            <button id="button_3on" type="button" class="btn btn-outline-success" onclick="button_3_on()" style="width: 5rem"><strong><i class="fa fa-bolt f-left"></i></strong></button> 
                            <button id="button_3off" type="button" class="btn btn-outline-danger" onclick="button_3_off()" style="width: 5rem"><strong><i class="fa fa-power-off f-left"></i></strong></button>
                        </div>
                    </div>
                    <div class="col m-3">
                        <strong> Purifiers </strong><br>
                        <div class="btn-group text-white" role="group" aria-label="Basic example">
                            <button id="button_4on" type="button" class="btn btn-outline-success" onclick="button_4_on()" style="width: 5rem"><strong><i class="fa fa-bolt f-left"></i></strong></button> 
                            <button id="button_4off" type="button" class="btn btn-outline-danger" onclick="button_4_off()" style="width: 5rem"><strong><i class="fa fa-power-off f-left"></i></strong></button>
                        </div>
                    </div>
                </div>
            </div>
          </div>
        </div>
      </div>
      <!-- <div class="row">
        <div class="col mt-3">
            <div class="card border-dark" style="height: 20rem">
                <div class="card-body">
                  <h5 class="card-title"><i class="fa fa-clipboard f-left"></i> Monitoring</h5>
                  <div class="row text-center">
                    <div class="col m-3">
                        <h3 id="title_value">Tes</h3>
                        <br>
                        <h3 id="counter_value">0</h3>
                    </div>
                  </div>
                </div>
              </div>
        </div>
      </div> -->
  </div>

</main>

<footer class="text-muted py-5 l-bg-blue-dark">
  <div class="container">
    <p class="float-end mb-1">
      <a href="#" class="text-white"><strong>Back to top</strong></a>
    </p>
    <p id="dates" class="mb-1 text-white"></p>
  </div>
</footer>


<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
<script>
  const input_webcam = document.getElementById("input_webcam")
  const button_webcam = document.getElementById("button_webcam")

  button_webcam.addEventListener("click", function() {
    
    if (input_webcam.value == "") {
      
      alert("Input Webcam Link")
    }else{
      
  
      // save localstorage
      localStorage.setItem("input_webcam", input_webcam.value)  

      alert("Success Save Webcam Link !")
      // refresh value
      document.getElementById("input_webcam").value = "";
    }
      
  })

    const getCurrentTimeDate = () => {
        let currentTimeDate = new Date()

        var weekday = new Array(7)
        weekday[0] = "SUN"
        weekday[1] = "MON"
        weekday[2] = "TUE"
        weekday[3] = "WED"
        weekday[4] = "THU"
        weekday[5] = "FRI"
        weekday[6] = "SAT"
        
        var month = new Array()
        month[0] = "JAN"
        month[1] = "FEB"
        month[2] = "MAR"
        month[3] = "APR"
        month[4] = "May"
        month[5] = "JUN"
        month[6] = "JUL"
        month[7] = "AUG"
        month[8] = "SEP"
        month[9] = "OCT"
        month[10] = "NOV"
        month[11] = "DEC"
        
        
        var hours   =  currentTimeDate.getHours()

        var minutes =  currentTimeDate.getMinutes()
        minutes = minutes < 10 ? '0'+minutes : minutes

         var AMPM = hours >= 12 ? 'PM' : 'AM'

        if(hours === 12){
            hours=12

        }else{

            hours = hours%12

        }

  

        var currentTime = `${hours}:${minutes}${AMPM}`
        var currentDay = weekday[currentTimeDate.getDay()]

        var currentDate  = currentTimeDate.getDate()
        var currentMonth = month[currentTimeDate.getMonth()]
        var CurrentYear = currentTimeDate.getFullYear()

        var fullDate = `${currentDate} ${currentMonth} ${CurrentYear}`


        document.getElementById("time").innerHTML = currentTime
        document.getElementById("day").innerHTML = currentDay
        document.getElementById("date").innerHTML = fullDate
        document.getElementById("dates").innerHTML = `Smart Aquarium System &copy ${CurrentYear}`

        
        setTimeout(getCurrentTimeDate, 500)
    


    }
    getCurrentTimeDate()
</script>
      
  </body>
</html>
)=====";
