chrome.app.runtime.onLaunched.addListener(function() {
  chrome.app.window.create('main.html', {
    id: 'main',
    bounds: { width: 1280, height: 1093 },
    resizable: false
  });
});