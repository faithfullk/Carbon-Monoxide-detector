

const char index_html[] PROGMEM = R"=====(

<!DOCTYPE HTML><html>
<head>
  <title>CO Monitoring System</title>
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    .menu-icon { display: block; cursor: pointer; z-index: 1; width: 24px; height: 18px; padding-top: 5px; position: absolute; top: 38px; left: 20px; }
    .menu-icon::before,
    .menu-icon::after { content: ""; display: block; background-color: #d6d6d6; height: 3px; width: 100%; position: absolute; left: 0; transition: transform 0.2s ease-out; }
    .menu-icon::before { top: 0; }
    .menu-icon::after { bottom: 0; }
    .menu-icon.active::before { transform: translateY(2.5px) rotate(45deg); }
    .menu-icon.active::after { transform: translateY(-2.5px) rotate(-45deg); }
    ul { list-style-type: none; margin: 0; padding: 0; display: none; position: absolute; top: 0px; left: 0; width: 100%; background-color: #414141; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2); z-index: 0; }
    li { text-align: center; margin: 10px; }
    a { display: block; padding: 10px; text-decoration: none; color: #d6d6d6; font-weight: bold; }
    nav.active ul { display: block; animation: slide-down 0.5s ease-out; }
    @keyframes slide-down 
    {
      0% 
      {
        transform: translateY(-100%);
      }
      100% 
      {
        transform: translateY(0%);
      }
    }
    html {font-family: Arial; display: inline-block; text-align: center;}
    p { font-size: 1.2rem;}
    body {  margin: 0; background-color: #050505; color: #d6d6d6}
    .topnav { overflow: hidden; background-color: #001929; font-size: 1.7rem;}
    .card {background-color: black; box-shadow: 0px 0px 12px 0px rgba(140,140,140,.5); color: #d6d6d6;}
    .cards { padding: 20px; max-width: 700px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); }
    .reading { font-size: 2.8rem; }
    .button { padding: 15px 32px; display: inline-block; margin: 4px 2px; box-shadow: 1px 1px 10px .1px rgba(140,140,140,.5); }
    .dropbtn { padding: 16px; width: 200px; border-radius: 8px; }
    .button,.dropbtn { border: none; color: white; text-align: center; background-color: #b60000; font-size: 16px; }
    .button:hover,.dropbtn:hover{background-color: #910000; cursor: pointer;}
  </style>
</head>
  <body>
    <nav>
      <div class="menu-icon"></div>
      <ul>
        <li><a href="#home">Home</a></li>
        <li><a href="#graph">Live Graph</a></li>
        <li><a href="#about">About</a></li>
      </ul>
    </nav>

<!--------- Home Page --------->
    <section id="home">
      <div class="topnav">
        <h4>CO Monitoring System</h4>
      </div>
      <div class="cards">
        <div id="card1" class="card">
          <h4>BOARD #1 - CARBON MONOXIDE</h4>
          <p><span class="reading"><span id="co1">NA</span> ppm</span></p>
          <button class="button" id="button1" onclick="toggleInfo(1)">More Info</button>
          <h4><span class="reading" id="info1" style="display: none;">
            <p>Max: <span id="mco1">NA</span> ppm</p>
            <p>Time Active: <span id="r1">NA</span> s</p>
          </span></h4>
        </div>
        <div id="card2" class="card">
          <h4>BOARD #2 - CARBON MONOXIDE</h4>
          <p><span class="reading"><span id="co2">NA</span> ppm</span></p>
          <button class="button" id="button2" onclick="toggleInfo(2)">More Info</button>
          <h4><span class="reading" id="info2" style="display: none;">
            <p>Max: <span id="mco2">NA</span> ppm</p>
            <p>Time Active: <span id="r2">NA</span> s</p>
          </span></h4>
        </div>
        <div id="card3" class="card">
          <h4>BOARD #3 - CARBON MONOXIDE</h4>
          <p><span class="reading"><span id="co3">NA</span> ppm</span></p>
          <button class="button" id="button3" onclick="toggleInfo(3)">More Info</button>
          <h4><span class="reading" id="info3" style="display: none;">
            <p>Max: <span id="mco3">NA</span> ppm</p>
            <p>Time Active: <span id="r3">NA</span> s</p>
          </span></h4>
        </div>
        <div id="card4" class="card">
          <h4>BOARD #4 - CARBON MONOXIDE</h4>
          <p><span class="reading"><span id="co4">NA</span> ppm</span></p>
          <button class="button" id="button4" onclick="toggleInfo(4)">More Info</button>
          <h4><span class="reading" id="info4" style="display: none;">
            <p>Max: <span id="mco4">NA</span> ppm</p>
            <p>Time Active: <span id="r4">NA</span> s</p>
          </span></h4>

        </div>
      </div>
    </section>

<!--------- Graphs Page --------->
    <section id="graph" style="display:none">
      <div class="topnav">
        <h4>Live Graph</h4>
      </div>
      <br>  
      <div>  
        <button class="dropbtn" onclick="toggleGraphs(1)">Board #1 &#9660;</button>
        <div id="graph-container1" style="opacity:0; height:1px;">
          <canvas id="myChart1a"></canvas>
          <canvas id="myChart1b"></canvas>
        </div>
      </div>      
      <br>      
      <div>
        <button class="dropbtn" onclick="toggleGraphs(2)">Board #2 &#9660;</button>
        <div id="graph-container2" style="opacity:0; height:1px;">
          <canvas id="myChart2a"></canvas>
          <canvas id="myChart2b"></canvas>
        </div>
      </div>       
      <br>      
      <div>
        <button class="dropbtn" onclick="toggleGraphs(3)">Board #3 &#9660;</button>
        <div id="graph-container3" style="opacity:0; height:1px;">
          <canvas id="myChart3a"></canvas>
          <canvas id="myChart3b"></canvas>
        </div>
      </div> 
      <br>      
      <div>
        <button class="dropbtn" onclick="toggleGraphs(4)">Board #4 &#9660;</button>
        <div id="graph-container4" style="opacity:0; height:1px;">
          <canvas id="myChart4a"></canvas>
          <canvas id="myChart4b"></canvas>
        </div>
      </div> 
         
    </section>
<!--------- About Page --------->
    <section id="about" style="display:none">
      <div class="topnav">
        <h4>About</h4>
      </div>
      <u><h1>Carbon Monoxide Safety</h1></u>
      <p>Carbon monoxide (CO) is a colorless, odorless gas that can be produced by incomplete combustion of fossil fuels such as natural gas, propane, gasoline, diesel fuel, and wood. It is highly toxic and can cause serious health problems, including death, when people are exposed to high levels of it.</p>
      <u><h2>Tips for Carbon Monoxide Safety</h2></u>
      <li>Install carbon monoxide detectors</li>
       <li>Keep appliances in good working order</li>
       <li>Proper ventilation</li>
       <li>Don't run engines indoors</li>
       <li>Be aware of the symptoms</li>
       <li>Keep vents clear</li>
       <li>Know the risks when using space heaters</li>
       <li>Use generators safely</li>
       For more information please visit the CDC website <a href="https://www.cdc.gov/co"> [HERE]</a>          
    </section>


<!--------- Scripts --------->
    <script>
      var graphContainers = document.querySelectorAll('[id^="graph-container"]');
      var timeouts = [];
      var cards = document.querySelectorAll('[id^="co"]');
      for (var i = 0; i < cards.length; i++) 
      {
        timeouts.push(null);
      }
    
//Info Toggle
      function toggleInfo(containerNum) 
      {
        var info = document.getElementById("info" + containerNum);
      var button = document.getElementById("button" + containerNum);
        if (info.style.display === "none") 
        {
          info.style.display = "block";
          button.textContent = "Close";
        } 
        else 
        {
          info.style.display = "none";
          button.textContent = "More Info";
        }
      }
      
//Graph Toggle
      function toggleGraphs(containerNum) 
      {
        for (var i = 0; i < graphContainers.length; i++) 
        {
          var otherGraphContainer = graphContainers[i];
          if (otherGraphContainer.id != ("graph-container" + containerNum) && otherGraphContainer.style.opacity == 1) 
          {
            otherGraphContainer.style.opacity = 0;
            otherGraphContainer.style.height = "1px";
            otherGraphContainer.style.transition = "opacity 0.5s ease-in-out, height 0.5s ease-in-out";
          }
        }
      
        var graphContainer = document.getElementById("graph-container" + containerNum);
        var isHidden = graphContainer.style.opacity == 0;

        if (isHidden) 
        {
          graphContainer.style.opacity = 1;
          graphContainer.style.height = "auto";
          graphContainer.style.transition = "opacity 0.5s ease-in-out, height 0.5s ease-in-out";
        } 
        else 
        {
          graphContainer.style.opacity = 0;
          graphContainer.style.height = "1px";
          graphContainer.style.transition = "opacity 0.5s ease-in-out, height 0.5s ease-in-out";
        }
      }
      
//Menu Navigation
      const menuIcon = document.querySelector('.menu-icon');
      const nav = document.querySelector('nav');
      const homeSection = document.querySelector('#home');
      const graphSection = document.querySelector('#graph');
      const aboutSection = document.querySelector('#about');
      
      //Opens/Closes the menu when it icon is clicked
      menuIcon.addEventListener('click', function() { menuIcon.classList.toggle('active'); nav.classList.toggle('active'); });

      // Listen for clicks on navigation links
      const navLinks = document.querySelectorAll('nav a');
      navLinks.forEach(link => {
        link.addEventListener('click', function(e) {
          e.preventDefault(); // Prevent the link from navigating to a new page
          const sectionId = link.getAttribute('href'); // Get the ID of the section to show
          
          //Closes any graph that's open if you click a nav link
          graphContainers.forEach(container => {
            if (container.style.opacity == 1) 
            {
              container.style.opacity = 0;
              container.style.height = "1px";
              container.style.transition = "opacity 0.5s ease-in-out, height 0.5s ease-in-out";
              container.querySelectorAll("canvas").forEach(canvas => {canvas.style.height = "0";});
            }
          });
          
          // Hide all sections and show the selected one
          homeSection.style.display = 'none';
          graphSection.style.display = 'none';
          aboutSection.style.display = 'none';
          document.querySelector(sectionId).style.display = 'block';
          // Toggle the active class on the menu icon and navigation menu
          menuIcon.classList.remove('active');
          nav.classList.remove('active');
        });
      });

//Graph Generation
      // Get the number of graph containers
    var numGraphs = graphContainers.length;
      
      // Create an array to store the chart objects
    var myCharts = [];

    // Loop through each graph container and create the charts
    for (var i = 1; i <= numGraphs; i++) 
      {
        var chartNameA = 'myChart' + i + 'a';
        var chartNameB = 'myChart' + i + 'b';

        var ctxA = document.getElementById(chartNameA).getContext('2d');
        var myChartA = new Chart(ctxA, {
          type: 'line',
          data: 
          {
            labels: [],
            datasets: [{
              label: 'One Minute',
              data: [],
              backgroundColor: 'rgba(255, 99, 132, 0.2)',
              borderColor: 'rgba(255, 99, 132, 1)',
              borderWidth: 1
            }]
          },
          options: {
            scales: {
              xAxes: [{
                  ticks: {
                    autoSkip: true,
                    maxTicksLimit: 6
                  }
                }],
                yAxes: [{
                  ticks: {
                    beginAtZero: true
                  }
                }]
              }
            }
        });

        var ctxB = document.getElementById(chartNameB).getContext('2d');
        var myChartB = new Chart(ctxB, {
          type: 'line',
          data: 
          {
            labels: [],
            datasets: [{
              label: 'One Minute',
              data: [],
              backgroundColor: 'rgba(255, 99, 132, 0.2)',
              borderColor: 'rgba(255, 99, 132, 1)',
              borderWidth: 1
            }]
          },
          options: {
            scales: {
              xAxes: [{
                  ticks: {
                    autoSkip: true,
                    maxTicksLimit: 6
                  }
                }],
                yAxes: [{
                  ticks: {
                    beginAtZero: true
                  }
                }]
              }
            }
        });

        // Store the chart objects in the array
        myCharts[i] = {
          a: myChartA,
          b: myChartB
        };
      }

//Event Listener
      if (!!window.EventSource) 
      {
        var source = new EventSource('/events');
 
        source.addEventListener('open', function(e) 
        {
          console.log("Events Connected");
        }, false);
        
        source.addEventListener('error', function(e) 
        {
          if (e.target.readyState != EventSource.OPEN) 
          {
            console.log("Events Disconnected");
          }
        }, false);
 
        source.addEventListener('message', function(e) 
        { 
          console.log("message", e.data); 
        }, false);
 
        source.addEventListener('new_readings', function(e) 
        { 
          console.log("new_readings", e.data);
          var obj = JSON.parse(e.data);
          document.getElementById("co"+obj.id).innerHTML = obj.carbon_monoxide.toFixed(2);
          document.getElementById("mco"+obj.id).innerHTML = obj.max_carbon_monoxide.toFixed(2);
          document.getElementById("r"+obj.id).innerHTML = obj.readingId;
          
          if (obj.carbon_monoxide > 100)
          {
            document.getElementById("card"+obj.id).style.backgroundColor = "red";
          }
          else if (obj.carbon_monoxide > 10)
          {
            document.getElementById("card"+obj.id).style.backgroundColor = "#fcb13b";
          }
          else
          {
            document.getElementById("card"+obj.id).style.backgroundColor = "#598cb6";
          }

        // Update chart with id "myChart" + obj.id + "a"
          var chartA = myCharts[obj.id].a;
          chartA.data.labels.push(obj.readingId);
          if (chartA.data.labels.length > 60) 
          {
          chartA.data.labels.shift();
          chartA.data.datasets[0].data.shift();
          }
          chartA.data.datasets[0].data.push(obj.carbon_monoxide.toFixed(2));
          chartA.update();

          // Update chart with id "myChart" + obj.id + "b"
          var chartB = myCharts[obj.id].b;
          chartB.data.labels.push(obj.readingId);
          if (chartB.data.labels.length > 3600) 
          {
            chartB.data.labels.shift();
            chartB.data.datasets[0].data.shift();
          }
          chartB.data.datasets[0].data.push(obj.carbon_monoxide.toFixed(2));
          chartB.update();

          //Starts a timer, if no new data in 10s the display goes back to NA
          if (timeouts[obj.id - 1]) 
          {
            clearTimeout(timeouts[obj.id - 1]);
          }

          timeouts[obj.id - 1] = setTimeout(function() 
            {
              document.getElementById("co"+obj.id).innerHTML = "NA";
              document.getElementById("mco"+obj.id).innerHTML = "NA";
              document.getElementById("r"+obj.id).innerHTML = "NA";
	      document.getElementById("card"+obj.id).style.backgroundColor = "black";
            
              var chartA = myCharts[obj.id].a;
              var chartB = myCharts[obj.id].b;
              // Delete all data in the charts
              chartA.data.labels = [];
              chartA.data.datasets[0].data = [];
              chartB.data.labels = [];
              chartB.data.datasets[0].data = [];
          }, 10000);
        }, false);
      }
    </script>
  </body>
  

</html>)=====";