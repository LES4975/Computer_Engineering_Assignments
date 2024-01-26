let count = 0; //Click counter
let squares = document.querySelectorAll(".box");
let clickedColor; //Answer color
let currentColor; //Normal color
let originalColor; //To save the original color
let wrongNum; //Answer box index
let timeleft = 30; //for Countdown
let ClikctheBox = false;
let startButton = document.querySelector("#start");
let resetButton = document.querySelector("#reset");

ColorGame();

//Let's Play the Game!

function ColorGame() {
  startButton.addEventListener("click", startGame);
  resetButton.addEventListener("click", resetGame);
}

//----------Function------------------------------------

//Select the color randomly
function ColorCode() {
  var randomColor = "#" + parseInt(Math.random() * 0xffffff).toString(16);
  if (randomColor == "#d7d7d7") {
    return ColorCode();
  }
  //I don't know why some color code output shorter than 7.
  //So, If a seven-character color code does not appear as a conditional statement, the color code will be generated again.
  if (randomColor.length < 7) {
    return ColorCode();
  }
  return randomColor;
}

//Fill the box with color
function fillSquare() {
  currentColor = ColorCode();

  for (var i = 0; i < squares.length; i++) {
    squares[i].style.backgroundColor = currentColor;
  }
}

//Find the different color box
function pickSquare() {
  let random = Math.floor(Math.random() * squares.length);
  clickedColor = wrongColor();
  squares[random].style.backgroundColor = clickedColor;
  console.log("BOX[" + random + "] is different!");
  return random;
}

//Find the wrong color
function wrongColor() {
  originalColor = currentColor;
  let resultColor = originalColor;

  //Modify the color hex code
  for (var i = 2; i < 7; i++) {
    if (i % 2 == 1) continue;
    if (originalColor[i] >= "0" && originalColor[i] <= "5") {
      changeNum = "a";
    } else if (originalColor[i] >= "6" && originalColor <= "9") {
      changeNum = "0";
    } else {
      changeNum = "2";
    }
    resultColor = resultColor.replace(resultColor[i], changeNum);
  }

  console.log("바뀐 색상 코드 : " + resultColor);
  return resultColor;
}

//If the color you clicked is different from the current color -> Increase counter +1

function CounterUp() {
  count = count + 1;
  document.getElementById("cnt").innerHTML = count;
}

// Countdown
function Count_time() {
  document.getElementById("time").style.color = "aliceblue";
  let timer = setInterval(function () {
    //time decrease by sec
    document.getElementById("time").innerHTML = timeleft;
    timeleft--;
    //Time Out
    if (timeleft < 10) document.getElementById("time").style.color = "#FF6A6A";
    if (timeleft < 5) document.getElementById("time").style.color = "#FF2222";
    if (timeleft < 0 || document.getElementById("start").disabled == false) {
      document.getElementById("time").innerHTML = "0";
      clearInterval(timer);
      clearTimeout(timer);
      ClikctheBox = false;
      squares[wrongNum].removeEventListener("click", SelectBox);
      if (timeleft < 0) alert("You made it!" + "\n" + "Total : " + count);
    }
  }, 1000);
}

//Choose the box
function SelectBox() {
  CounterUp();
  ClikctheBox = true;
  if (ClikctheBox) {
    ClikctheBox = false;
    squares[wrongNum].removeEventListener("click", SelectBox);
    playingGame();
  }
}

//Disable the START button
function disableSTART() {
  $("#start").prop("disabled", true);
  document.getElementById("start").style.backgroundColor = "rgb(74, 74, 74)";
  document.getElementById("start").style.color = "rgb(24, 24, 24)";
}
//Activate the START button
function activeSTART() {
  $("#start").prop("disabled", false);
  document.getElementById("start").style.backgroundColor = "dodgerblue";
  document.getElementById("start").style.color = "rgb(169, 204, 229)";
}

//Operate the game
function startGame() {
  Count_time();
  playingGame();

  disableSTART();
}

//Reset the game
function resetGame() {
  init();
  activeSTART();
  document.getElementById("time").style.color = "#000000";
  ColorGame();
}

//Initialize the game
function init() {
  timeleft = 30;
  document.getElementById("time").style.color = "aliceblue";
  document.getElementById("time").innerHTML = timeleft;
  count = 0;
  document.getElementById("cnt").innerHTML = count;
  document.getElementById("gamebox").style.backgroundColor = "rgb(74, 74, 74)";
  for (var i = 0; i < 16; i++)
    document.querySelectorAll(".box")[i].style.backgroundColor = "grey";
}

//Game playing
function playingGame() {
  document.getElementById("gamebox").style.backgroundColor =
    "rgb(215, 215, 215)";
  fillSquare();
  console.log("CurrentColor = " + currentColor);
  wrongNum = pickSquare();
  squares[wrongNum].addEventListener("click", SelectBox);
}
