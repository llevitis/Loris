<<<<<<< 3a82da2167300510bdffb3fc9a433e97ade0ee28
<<<<<<< bc7938d0b8d1889c1d0277201c997f4c63a3db75
!function(modules){function __webpack_require__(moduleId){if(installedModules[moduleId])return installedModules[moduleId].exports;var module=installedModules[moduleId]={exports:{},id:moduleId,loaded:!1};return modules[moduleId].call(module.exports,module,module.exports,__webpack_require__),module.loaded=!0,module.exports}var installedModules={};return __webpack_require__.m=modules,__webpack_require__.c=installedModules,__webpack_require__.p="",__webpack_require__(0)}([function(module,exports){"use strict";function formatColumn(column,cell,rowData){if("PSCID"===column){var url=loris.BaseURL+"/"+rowData[1]+"/";return React.createElement("td",null,React.createElement("a",{href:url},cell))}if("Feedback"===column)switch(cell){case"1":return React.createElement("td",{style:{background:"#E4A09E"}},"opened");case"2":return React.createElement("td",{style:{background:"#EEEEAA"}},"answered");case"3":return React.createElement("td",{style:{background:"#99CC99"}},"closed");case"4":return React.createElement("td",{style:{background:"#99CCFF"}},"comment");default:return React.createElement("td",null,"None")}return"Scan Done"===column&&"Y"===cell?React.createElement("td",{className:"scanDoneLink"},React.createElement("a",{href:"#",onClick:loris.loadFilteredMenuClickHandler("imaging_browser/",{pscid:rowData[2]})},cell)):"Study Consent"===column?null===cell||"not_answered"===cell?React.createElement("td",null,"Not Answered"):"yes"===cell?React.createElement("td",null,"Yes"):React.createElement("td",null,"No"):React.createElement("td",null,cell)}Object.defineProperty(exports,"__esModule",{value:!0}),window.formatColumn=formatColumn,exports.default=formatColumn}]);
=======
!function(e){function t(n){if(r[n])return r[n].exports;var a=r[n]={exports:{},id:n,loaded:!1};return e[n].call(a.exports,a,a.exports,t),a.loaded=!0,a.exports}var r={};return t.m=e,t.c=r,t.p="",t(0)}([function(e,t){"use strict";function r(e,t,r){if("PSCID"===e){var n=loris.BaseURL+"/"+r[1]+"/";return React.createElement("td",null,React.createElement("a",{href:n},t))}if("Feedback"===e)switch(t){case"1":return React.createElement("td",{style:{background:"#E4A09E"}},"opened");case"2":return React.createElement("td",{style:{background:"#EEEEAA"}},"answered");case"3":return React.createElement("td",{style:{background:"#99CC99"}},"closed");case"4":return React.createElement("td",{style:{background:"#99CCFF"}},"comment");default:return React.createElement("td",null,"None")}return"Scan Done"===e&&"Y"===t?React.createElement("td",{className:"scanDoneLink"},React.createElement("a",{href:"#",onClick:loris.loadFilteredMenuClickHandler("imaging_browser",{pscid:r[2]})},t)):React.createElement("td",null,t)}Object.defineProperty(t,"__esModule",{value:!0}),window.formatColumn=r,t.default=r}]);
>>>>>>> Added configured studies, too
=======
!function(e){function t(n){if(r[n])return r[n].exports;var a=r[n]={exports:{},id:n,loaded:!1};return e[n].call(a.exports,a,a.exports,t),a.loaded=!0,a.exports}var r={};return t.m=e,t.c=r,t.p="",t(0)}([function(e,t){"use strict";function r(e,t,r,n){if(loris.hiddenHeaders.indexOf(e)>-1)return null;var a={};n.forEach(function(e,t){a[e]=r[t]},this);var c=[];if("yes"===a["Consent To Study"]&&c.push("bg-danger"),c=c.join(" "),"PSCID"===e){var l=loris.BaseURL+"/"+r[1]+"/";return React.createElement("td",null,React.createElement("a",{href:l},t))}if("Feedback"===e)switch(t){case"1":return React.createElement("td",{style:{background:"#E4A09E"}},"opened");case"2":return React.createElement("td",{style:{background:"#EEEEAA"}},"answered");case"3":return React.createElement("td",{style:{background:"#99CC99"}},"closed");case"4":return React.createElement("td",{style:{background:"#99CCFF"}},"comment");default:return React.createElement("td",null,"None")}return"Scan Done"===e&&"Y"===t?React.createElement("td",{className:"scanDoneLink"},React.createElement("a",{href:"#",onClick:loris.loadFilteredMenuClickHandler("imaging_browser",{pscid:r[2]})},t)):React.createElement("td",null,t)}Object.defineProperty(t,"__esModule",{value:!0}),window.formatColumn=r,t.default=r}]);
>>>>>>> working on modifying the appearance of consent for study_consent being set to no
//# sourceMappingURL=columnFormatter.js.map