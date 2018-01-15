!function(modules){function __webpack_require__(moduleId){if(installedModules[moduleId])return installedModules[moduleId].exports;var module=installedModules[moduleId]={exports:{},id:moduleId,loaded:!1};return modules[moduleId].call(module.exports,module,module.exports,__webpack_require__),module.loaded=!0,module.exports}var installedModules={};return __webpack_require__.m=modules,__webpack_require__.c=installedModules,__webpack_require__.p="",__webpack_require__(0)}([function(module,exports){"use strict";Object.defineProperty(exports,"__esModule",{value:!0});var _typeof="function"==typeof Symbol&&"symbol"==typeof Symbol.iterator?function(obj){return typeof obj}:function(obj){return obj&&"function"==typeof Symbol&&obj.constructor===Symbol&&obj!==Symbol.prototype?"symbol":typeof obj},StaticDataTable=React.createClass({displayName:"StaticDataTable",mixins:[React.addons.PureRenderMixin],propTypes:{Headers:React.PropTypes.array.isRequired,Data:React.PropTypes.array.isRequired,RowNumLabel:React.PropTypes.string,getFormattedCell:React.PropTypes.func,onSort:React.PropTypes.func},componentDidMount:function(){jQuery.fn.DynamicTable&&(this.props.freezeColumn?$("#dynamictable").DynamicTable({freezeColumn:this.props.freezeColumn}):$("#dynamictable").DynamicTable());var modulePrefs=JSON.parse(localStorage.getItem("modulePrefs"));null===modulePrefs&&(modulePrefs={}),void 0===modulePrefs[loris.TestName]&&(modulePrefs[loris.TestName]={},modulePrefs[loris.TestName].rowsPerPage=this.state.RowsPerPage);var rowsPerPage=modulePrefs[loris.TestName].rowsPerPage;this.setState({RowsPerPage:rowsPerPage}),this.modulePrefs=modulePrefs},componentDidUpdate:function(prevProps,prevState){if(jQuery.fn.DynamicTable&&(this.props.freezeColumn?$("#dynamictable").DynamicTable({freezeColumn:this.props.freezeColumn}):$("#dynamictable").DynamicTable()),this.props.onSort&&(this.state.SortColumn!==prevState.SortColumn||this.state.SortOrder!==prevState.SortOrder)){var index=this.getSortedRows();this.props.onSort(index,this.props.Data,this.props.Headers)}},getInitialState:function(){return{PageNumber:1,SortColumn:-1,SortOrder:"ASC",RowsPerPage:20}},getDefaultProps:function(){return{Headers:[],Data:{},RowNumLabel:"No.",Filter:{}}},changePage:function(pageNo){this.setState({PageNumber:pageNo})},setSortColumn:function(colNumber){var that=this;return function(e){that.state.SortColumn===colNumber?that.setState({SortOrder:"ASC"===that.state.SortOrder?"DESC":"ASC"}):that.setState({SortColumn:colNumber})}},changeRowsPerPage:function(val){var rowsPerPage=val.target.value,modulePrefs=this.modulePrefs;modulePrefs[loris.TestName].rowsPerPage=rowsPerPage,localStorage.setItem("modulePrefs",JSON.stringify(modulePrefs)),this.setState({RowsPerPage:rowsPerPage,PageNumber:1})},downloadCSV:function(csvData){var csvworker=new Worker(loris.BaseURL+"/js/workers/savecsv.js");csvworker.addEventListener("message",function(e){var dataURL,dataDate,link;"SaveCSV"===e.data.cmd&&(dataDate=(new Date).toISOString(),dataURL=window.URL.createObjectURL(e.data.message),link=document.createElement("a"),link.download="data-"+dataDate+".csv",link.type="text/csv",link.href=dataURL,document.body.appendChild(link),$(link)[0].click(),document.body.removeChild(link))}),csvworker.postMessage({cmd:"SaveFile",data:csvData,headers:this.props.Headers,identifiers:this.props.RowNameMap})},countFilteredRows:function(){for(var filterMatchCount=0,filterValuesCount=this.props.Filter?Object.keys(this.props.Filter).length:0,tableData=this.props.Data,headersData=this.props.Headers,i=0;i<tableData.length;i++){for(var headerCount=0,j=0;j<headersData.length;j++){var data=tableData[i]?tableData[i][j]:null;this.hasFilterKeyword(headersData[j],data)&&headerCount++}headerCount===filterValuesCount&&filterMatchCount++}var hasFilters=0!==filterValuesCount;return 0===filterMatchCount&&hasFilters?0:0===filterMatchCount?tableData.length:filterMatchCount},toCamelCase:function(str){return str.replace(/(?:^\w|[A-Z]|\b\w|\s+)/g,function(match,index){return 0===Number(match)?"":0===index?match.toLowerCase():match.toUpperCase()})},getSortedRows:function(){for(var index=[],i=0;i<this.props.Data.length;i+=1){var val=this.props.Data[i][this.state.SortColumn]||void 0;this.state.SortColumn===-1&&(val=i+1);var isString="string"==typeof val||val instanceof String,isNumber=!isNaN(val)&&"object"!==("undefined"==typeof val?"undefined":_typeof(val));val="."===val?null:isNumber?Number(val):isString?val.toLowerCase():void 0,this.props.RowNameMap?index.push({RowIdx:i,Value:val,Content:this.props.RowNameMap[i]}):index.push({RowIdx:i,Value:val,Content:i+1})}return index.sort(function(a,b){if("ASC"===this.state.SortOrder){if(a.Value===b.Value){if(a.RowIdx<b.RowIdx)return-1;if(a.RowIdx>b.RowIdx)return 1}if(null===a.Value||"undefined"==typeof a.Value)return-1;if(null===b.Value||"undefined"==typeof b.Value)return 1;if(a.Value<b.Value)return-1;if(a.Value>b.Value)return 1}else{if(a.Value===b.Value){if(a.RowIdx<b.RowIdx)return 1;if(a.RowIdx>b.RowIdx)return-1}if(null===a.Value||"undefined"==typeof a.Value)return 1;if(null===b.Value||"undefined"==typeof b.Value)return-1;if(a.Value<b.Value)return 1;if(a.Value>b.Value)return-1}return 0}.bind(this)),index},hasFilterKeyword:function(headerData,data){var header=this.toCamelCase(headerData),filterData=null,exactMatch=!1;if(this.props.Filter[header]&&(filterData=this.props.Filter[header].value,exactMatch=this.props.Filter[header].exactMatch),null===filterData||null===data)return!1;if("number"==typeof filterData){var intData=Number.parseInt(data,10);return filterData===intData}if("string"==typeof filterData){var searchKey=filterData.toLowerCase(),searchString=data.toLowerCase();return exactMatch?searchString===searchKey:searchString.indexOf(searchKey)>-1}if("object"===("undefined"==typeof filterData?"undefined":_typeof(filterData)))for(var match=!1,i=0;i<filterData.length;i+=1){var searchKey2=filterData[i].toLowerCase(),searchString2=data.toLowerCase();if(match=searchString2.indexOf(searchKey2)>-1)return!0}return!1},render:function(){if(null===this.props.Data||0===this.props.Data.length)return React.createElement("div",{className:"alert alert-info no-result-found-panel"},React.createElement("strong",null,"No result found."));for(var rowsPerPage=this.state.RowsPerPage,headers=[React.createElement("th",{key:"th_col_0",onClick:this.setSortColumn(-1)},this.props.RowNumLabel)],i=0;i<this.props.Headers.length;i+=1)if("undefined"==typeof loris.hiddenHeaders||loris.hiddenHeaders.indexOf(this.props.Headers[i])===-1){var colIndex=i+1;this.props.Headers[i]===this.props.freezeColumn?headers.push(React.createElement("th",{key:"th_col_"+colIndex,id:this.props.freezeColumn,onClick:this.setSortColumn(i)},this.props.Headers[i])):headers.push(React.createElement("th",{key:"th_col_"+colIndex,onClick:this.setSortColumn(i)},this.props.Headers[i]))}for(var rows=[],curRow=[],index=this.getSortedRows(),matchesFound=0,filteredRows=this.countFilteredRows(),currentPageRow=rowsPerPage*(this.state.PageNumber-1),filteredData=[],_i=0;_i<this.props.Data.length&&rows.length<rowsPerPage;_i++){curRow=[];for(var filterMatchCount=0,j=0;j<this.props.Headers.length;j+=1){var data="Unknown";this.props.Data[index[_i].RowIdx]&&(data=this.props.Data[index[_i].RowIdx][j]),this.hasFilterKeyword(this.props.Headers[j],data)&&(filterMatchCount++,filteredData.push(this.props.Data[index[_i].RowIdx]));var key="td_col_"+j;this.props.getFormattedCell?(data=this.props.getFormattedCell(this.props.Headers[j],data,this.props.Data[index[_i].RowIdx],this.props.Headers),null!==data&&curRow.push(React.addons.createFragment({data:data}))):curRow.push(React.createElement("td",{key:key},data))}if(Object.keys(this.props.Filter).length===filterMatchCount&&(matchesFound++,matchesFound>currentPageRow)){var rowIndex=index[_i].Content;rows.push(React.createElement("tr",{key:"tr_"+rowIndex,colSpan:headers.length},React.createElement("td",null,rowIndex),curRow))}}var RowsPerPageDropdown=React.createElement("select",{className:"input-sm perPage",onChange:this.changeRowsPerPage,value:this.state.RowsPerPage},React.createElement("option",null,"20"),React.createElement("option",null,"50"),React.createElement("option",null,"100"),React.createElement("option",null,"1000"),React.createElement("option",null,"5000"),React.createElement("option",null,"10000")),csvData=this.props.Data;return this.props.Filter&&filteredData.length>0&&(csvData=filteredData),React.createElement("div",{className:"panel panel-default"},React.createElement("div",{className:"table-header panel-heading"},React.createElement("div",{className:"row"},React.createElement("div",{className:"col-xs-12"},rows.length," rows displayed of ",filteredRows,". (Maximum rows per page: ",RowsPerPageDropdown,")",React.createElement("div",{className:"pull-right"},React.createElement(PaginationLinks,{Total:filteredRows,onChangePage:this.changePage,RowsPerPage:rowsPerPage,Active:this.state.PageNumber}))))),React.createElement("table",{className:"table table-hover table-primary table-bordered",id:"dynamictable"},React.createElement("thead",null,React.createElement("tr",{className:"info"},headers)),React.createElement("tbody",null,rows)),React.createElement("div",{className:"panel-footer table-footer"},React.createElement("div",{className:"row"},React.createElement("div",{className:"col-xs-12"},React.createElement("div",{className:"col-xs-12 footerText"},rows.length," rows displayed of ",filteredRows,". (Maximum rows per page: ",RowsPerPageDropdown,")"),React.createElement("div",{className:"col-xs-6"},React.createElement("button",{className:"btn btn-primary downloadCSV",onClick:this.downloadCSV.bind(null,csvData)},"Download Table as CSV")),React.createElement("div",{className:"pull-right"},React.createElement(PaginationLinks,{Total:filteredRows,onChangePage:this.changePage,RowsPerPage:rowsPerPage,Active:this.state.PageNumber}))))))}}),RStaticDataTable=React.createFactory(StaticDataTable);window.StaticDataTable=StaticDataTable,window.RStaticDataTable=RStaticDataTable,exports.default=StaticDataTable}]);
//# sourceMappingURL=StaticDataTable.js.map