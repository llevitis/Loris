!function (modules) {
    function __webpack_require__(moduleId) {
        if (installedModules[moduleId]) return installedModules[moduleId].exports;
        var module = installedModules[moduleId] = {exports: {}, id: moduleId, loaded: !1};
        return modules[moduleId].call(module.exports, module, module.exports, __webpack_require__), module.loaded = !0, module.exports
    }

    var installedModules = {};
    return __webpack_require__.m = modules, __webpack_require__.c = installedModules, __webpack_require__.p = "", __webpack_require__(0)
}([function (module, exports) {
    "use strict";

    function formatColumn(column, cell, rowData, rowHeaders) {
        if (loris.hiddenHeaders.indexOf(column) > -1) return null;
        var classes = [];
        var row = {};
        rowHeaders.forEach(function(header, index) {
            row[header] = rowData[index]
        }, this);
        if ("PSCID" === column) {
            var url = loris.BaseURL + "/" + row['DCCID'] + "/";
            return React.createElement("td", null, React.createElement("a", {href: url}, cell))
        }
        if ("Feedback" === column) switch (cell) {
            case"1":
                return React.createElement("td", {style: {background: "#E4A09E"}}, "opened");
            case"2":
                return React.createElement("td", {style: {background: "#EEEEAA"}}, "answered");
            case"3":
                return React.createElement("td", {style: {background: "#99CC99"}}, "closed");
            case"4":
                return React.createElement("td", {style: {background: "#99CCFF"}}, "comment");
            default:
                return React.createElement("td", null, "None")
        }
        return "Scan Done" === column && "Y" === cell ? React.createElement("td", {className: "scanDoneLink"}, React.createElement("a", {
            href: "#",
            onClick: loris.loadFilteredMenuClickHandler("imaging_browser/", {pscid: rowData[2]})
        }, cell)) : ("no" === row["Consent To Study"] && classes.push("bg-danger"), classes = classes.join(" "), React.createElement("td", {
            className: classes
        }, cell))
    }
    Object.defineProperty(exports, "__esModule", {value: !0}), window.formatColumn = formatColumn, exports.default = formatColumn
}]);
