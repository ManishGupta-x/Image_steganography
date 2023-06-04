function openTab(tabName) {
    var i, tabs, contents;
    tabs = document.getElementsByClassName("tab");
    contents = document.getElementsByClassName("content");
  
    for (i = 0; i < tabs.length; i++) {
      tabs[i].classList.remove("active");
      contents[i].style.display = "none";
    }
  
    document.getElementById(tabName).style.display = "block";
    document.getElementById(tabName + "-tab").classList.add("active");
  }
  
  
  
  function goToOriginalEncodePage() {
    const originalEncodePage = document.getElementById("encode");
    const duplicateEncodePage = document.getElementById("encode-duplicate");
    originalEncodePage.style.display = "block";
    duplicateEncodePage.style.display = "none";
  }
  
  // Function to handle form submission and create text file
function createTextFile(event) {
  event.preventDefault(); // Prevent form submission

  const message = document.getElementById('message-box').value;

  // Check if the message is empty
  if (message.trim() === '') {
    alert('Please enter a message');
    return;
  }

  const textBlob = new Blob([message], { type: 'text/plain' });

  const link = document.createElement('a');
  link.href = URL.createObjectURL(textBlob);
  link.download = 'message.txt';
  link.click();

  URL.revokeObjectURL(link.href);
}

// Function to handle tab switching
function openTab(tabName) {
  const tabs = document.getElementsByClassName('tab');
  const contents = document.getElementsByClassName('content');

  for (let i = 0; i < tabs.length; i++) {
    tabs[i].classList.remove('active');
    contents[i].style.display = 'none';
  }

  document.getElementById(tabName).style.display = 'block';
  document.getElementById(tabName + '-tab').classList.add('active');
}
