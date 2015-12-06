// app module
var demoApp = angular.module('demoApp', []);

// routes
demoApp.config(function ($routeProvider) {

   $routeProvider
    .when('/',
        {
            controller: 'HomeController',
            templateUrl: 'views/menu.html'
        })
    .when('/about',
        {
            controller: 'AboutController',
            templateUrl: 'views/about.html'
        })
       .when('/table',
       {
           controller: 'TimestampController',
           templateUrl: 'views/Timestamp-summary.html'
       })
    .when('/posts',
        {
            controller: 'PostController',
            templateUrl: 'views/posts.html'
        })
     .when('/welcome',
       {
           controller: 'WelcomeController',
           templateUrl: 'views/description.html'
       })
       .when('/description',
       {
           controller: 'InfoController',
           templateUrl: 'views/description.html'
       })
       .when('/door',
       {
           controller: 'DoorController',
           templateUrl: 'views/door.html'
       })
       .when('/window',
       {
           controller: 'WindowController',
           templateUrl: 'views/window.html'
       })
    .otherwise({ redirectTo: '/' });

});