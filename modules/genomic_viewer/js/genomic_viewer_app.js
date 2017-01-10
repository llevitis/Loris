'use strict';

var _slicedToArray = function () { function sliceIterator(arr, i) { var _arr = []; var _n = true; var _d = false; var _e = undefined; try { for (var _i = arr[Symbol.iterator](), _s; !(_n = (_s = _i.next()).done); _n = true) { _arr.push(_s.value); if (i && _arr.length === i) break; } } catch (err) { _d = true; _e = err; } finally { try { if (!_n && _i["return"]) _i["return"](); } finally { if (_d) throw _e; } } return _arr; } return function (arr, i) { if (Array.isArray(arr)) { return arr; } else if (Symbol.iterator in Object(arr)) { return sliceIterator(arr, i); } else { throw new TypeError("Invalid attempt to destructure non-iterable instance"); } }; }();

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (!self) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return call && (typeof call === "object" || typeof call === "function") ? call : self; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) Object.setPrototypeOf ? Object.setPrototypeOf(subClass, superClass) : subClass.__proto__ = superClass; }

/*
 * The control panel is used to input the genomic location to view.
 * It also provide ways to navigate namely zomming and scrolling.
 */
var ControlPanel = function (_React$Component) {
  _inherits(ControlPanel, _React$Component);

  function ControlPanel(props) {
    _classCallCheck(this, ControlPanel);

    var _this = _possibleConstructorReturn(this, Object.getPrototypeOf(ControlPanel).call(this, props));

    _this.state = {
      genomicRange: props.genomicRange
    };

    _this.handleChange = _this.handleChange.bind(_this);
    _this.handleSubmit = _this.handleSubmit.bind(_this);
    _this.handleNavigation = _this.handleNavigation.bind(_this);
    return _this;
  }

  // Update the state only if a new genomicRange is received.


  _createClass(ControlPanel, [{
    key: 'componentWillReceiveProps',
    value: function componentWillReceiveProps(nextProps) {
      if (nextProps.hasOwnProperty('genomicRange')) {
        this.setState({ genomicRange: nextProps.genomicRange });
      }
    }

    // Update the state on each key sent.

  }, {
    key: 'handleChange',
    value: function handleChange(event) {
      this.setState({ genomicRange: event.target.value.trim() });
    }

    // Submit the new value to the GenomicViewerApp

  }, {
    key: 'handleSubmit',
    value: function handleSubmit(event) {
      event.preventDefault();
      this.props.setGenomicRange(this.state.genomicRange);
    }

    // Function to handle the zomming and the moving.

  }, {
    key: 'handleNavigation',
    value: function handleNavigation(event) {
      event.preventDefault();

      var newGenomicRange = void 0,
          newFrom = void 0,
          newTo = void 0,
          rangeSpan = void 0;

      var _state$genomicRange$m = this.state.genomicRange.match(/(^chr|^Chr|^CHR|^)([0-9]|[1][0-9]|[2][0-2]|[xXyYmM]):([0-9, ]+)-([0-9, ]+)/i);

      var _state$genomicRange$m2 = _slicedToArray(_state$genomicRange$m, 5);

      var genomicRange = _state$genomicRange$m2[0];
      var prefix = _state$genomicRange$m2[1];
      var chr = _state$genomicRange$m2[2];
      var from = _state$genomicRange$m2[3];
      var to = _state$genomicRange$m2[4];


      from = parseInt(from);
      to = parseInt(to);
      rangeSpan = to - from;

      switch (event.target.id) {
        case 'control-chevron-left':
          // Move 90% of the viewer's span toward 5' (left)
          newFrom = from - Math.round(rangeSpan * 0.9);
          newTo = to - Math.round(rangeSpan * 0.9);
          break;
        case 'control-chevron-zoom-out':
          // Increase the viewer' span 2 times keeping center
          newFrom = from - Math.round(rangeSpan * 0.5);
          newTo = to + Math.round(rangeSpan * 0.5);
          break;
        case 'control-chevron-zoom-in':
          // Reduce the viewer' span by 50% keeping center
          newFrom = from + Math.round(rangeSpan * 0.25);
          newTo = to - Math.round(rangeSpan * 0.25);
          break;
        case 'control-chevron-right':
          // Move 90% of the viewer's span toward 3' (right)
          newFrom = from + Math.round(rangeSpan * 0.9);
          newTo = to + Math.round(rangeSpan * 0.9);
          break;
      }

      newGenomicRange = 'chr'.concat(chr, ':', newFrom, '-', newTo);
      this.props.setGenomicRange(newGenomicRange);
    }
  }, {
    key: 'render',
    value: function render() {
      return React.createElement(
        'div',
        null,
        React.createElement(
          'center',
          null,
          React.createElement(
            'form',
            { onSubmit: this.handleSubmit },
            React.createElement(
              'div',
              { className: 'searche-input' },
              React.createElement('input', {
                type: 'text',
                size: '30',
                value: this.state.genomicRange,
                onChange: this.handleChange,
                placeholder: 'Ex: chrY:15012776-15036313',
                pattern: '(^chr|^Chr|^CHR|^)([0-9]|[1][0-9]|[2][0-2]|[xXyYmM]):([0-9, ]+)-([0-9, ]+)'
              }),
              React.createElement('span', {
                id: 'control-glyphicon-search',
                className: 'glyphicon glyphicon-search',
                onClick: this.handleSubmit })
            ),
            React.createElement(
              'div',
              { className: 'navigation-buttons' },
              React.createElement('span', {
                id: 'control-chevron-left',
                className: 'glyphicon glyphicon-chevron-left',
                onClick: this.handleNavigation
              }),
              React.createElement('span', {
                id: 'control-chevron-zoom-out',
                className: 'glyphicon glyphicon-zoom-out',
                onClick: this.handleNavigation
              }),
              React.createElement('span', {
                id: 'control-chevron-zoom-in',
                className: 'glyphicon glyphicon-zoom-in',
                onClick: this.handleNavigation
              }),
              React.createElement('span', {
                id: 'control-chevron-right',
                className: 'glyphicon glyphicon-chevron-right',
                onClick: this.handleNavigation
              })
            )
          )
        )
      );
    }
  }]);

  return ControlPanel;
}(React.Component);

ControlPanel.propTypes = {
  genomicRange: React.PropTypes.string,
  setGenomicRange: React.PropTypes.func.isRequired
};

ControlPanel.defaultProps = {
  genomicRange: ""
};

var Track = function (_React$Component2) {
  _inherits(Track, _React$Component2);

  function Track(props) {
    _classCallCheck(this, Track);

    var _this2 = _possibleConstructorReturn(this, Object.getPrototypeOf(Track).call(this, props));

    _this2.state = {};
    return _this2;
  }

  _createClass(Track, [{
    key: 'render',
    value: function render() {
      var containerStyle = {
        display: "flex",
        flexWrap: "nowrap",
        justifyContent: "space-between",
        alignItems: "center"
      };
      return React.createElement(
        'tr',
        { className: 'track' },
        React.createElement(
          'td',
          null,
          React.createElement(
            'div',
            { className: 'track-handle', style: containerStyle },
            React.createElement(
              'div',
              { className: 'track-title' },
              this.props.title
            ),
            React.createElement(
              'div',
              { className: 'track-yAxis' },
              this.props.yAxis
            )
          )
        ),
        React.createElement(
          'td',
          null,
          React.createElement(
            'div',
            { className: 'track-content' },
            this.props.children
          )
        )
      );
    }
  }]);

  return Track;
}(React.Component);

Track.propTypes = {
  title: React.PropTypes.node.isRequired,
  yAxis: React.PropTypes.node,
  children: React.PropTypes.arrayOf(React.PropTypes.element)
};

Track.defaultProps = {
  children: []
};

/*
 * Using a reduce definition of gene prediction tracks convention @
 * https://genome.ucsc.edu/goldenPath/help/hgTracksHelp.html#GeneDisplay
 * 
 * Coding exons are represented by blocks connected by horizontal lines representing
 * introns. The 5' and 3' untranslated regions (UTRs) are displayed as thinner
 * blocks on the leading and trailing ends of the aligning regions. 
 * Arrowheads on the connecting intron lines indicate the direction of
 * transcription.
 */

var Gene = function (_React$Component3) {
  _inherits(Gene, _React$Component3);

  function Gene(props) {
    _classCallCheck(this, Gene);

    var _this3 = _possibleConstructorReturn(this, Object.getPrototypeOf(Gene).call(this, props));

    _this3.state = {
      canvasHeight: 20
    };

    _this3.showGeneDetails = _this3.showGeneDetails.bind(_this3);
    return _this3;
  }

  _createClass(Gene, [{
    key: 'componentDidMount',
    value: function componentDidMount() {
      this.draw(this.props.genomicRange);
    }
  }, {
    key: 'componentWillReceiveProps',
    value: function componentWillReceiveProps(nextProps) {
      if (nextProps.hasOwnProperty('genomicRange')) {
        this.draw(nextProps.genomicRange);
      }
    }

    /*
     * Adjust the canvas width the draw the gene according to the displayed
     * genomic range. 
     */

  }, {
    key: 'draw',
    value: function draw(genomicRange) {
      var canvas = this.refs.thatCanvas;
      if (canvas) {
        var width = this.refs.thatDiv.getDOMNode().clientWidth;
        var height = this.state.canvasHeight;
        var pattern = /(^chr|^Chr|^CHR|^)([0-9]|[1][0-9]|[2][0-2]|[xXyYmM]):([0-9, ]+)-([0-9, ]+)/;

        var _props$genomicRange$m = this.props.genomicRange.match(pattern);

        var _props$genomicRange$m2 = _slicedToArray(_props$genomicRange$m, 5);

        var _genomicRange = _props$genomicRange$m2[0];
        var prefix = _props$genomicRange$m2[1];
        var chromosome = _props$genomicRange$m2[2];
        var start = _props$genomicRange$m2[3];
        var end = _props$genomicRange$m2[4];

        // Adjust width and height according to screen size

        canvas.getDOMNode().width = width;
        canvas.getDOMNode().height = height;

        // Determine the scale between the canvas width and the displayed genomicRange
        // Unit: pixel per base pair
        var xScale = width / (parseInt(end) - parseInt(start));

        var accession_number = this.props.accession_number;
        var chrom = this.props.chrom;
        var strand = this.props.strand;
        var txStart = this.props.txStart;
        var txEnd = this.props.txEnd;
        var cdsStart = this.props.cdsStart;
        var cdsEnd = this.props.cdsEnd;
        var exonStarts = this.props.exonStarts;
        var exonEnds = this.props.exonEnds;
        var name = this.props.name;

        var ctx = canvas.getDOMNode().getContext('2d');

        var y = height / 2;
        var x1 = txStart <= start ? 0 : (txStart - start) * xScale;
        var x2 = txEnd >= end ? width : (txEnd - start) * xScale;

        // Add the strand background
        // XLB 20161219 :: For some reason, the image are reversed... I can't explain so I reversed the ternary results.
        var imageName = strand == "+" ? 'reverseBackground' : 'forwardBackground';
        var img = document.getElementById(imageName);
        var background = ctx.createPattern(img, 'repeat');
        ctx.fillStyle = background;
        ctx.fillRect(x1, 7.5, x2 - x1, 5);

        // Draw horizontal lines representing introns.
        ctx.strokeStyle = "navy";
        ctx.beginPath();
        ctx.moveTo(x1, y);
        ctx.lineTo(x2, y);
        ctx.stroke();

        // Add UTR's
        // left


        // Add exons
        if (exonStarts.length != exonEnds.length) {
          console.error('Exon counts differs.');
        }

        var count = exonStarts.length;
        for (var i = 0; i < count; i++) {
          var exonStart = parseInt(exonStarts[i]);
          var exonEnd = parseInt(exonEnds[i]);

          if (exonStart < end && exonEnd > start) {
            if (exonStart <= cdsStart) {
              if (exonEnd <= cdsStart) {
                // The whole exon is in UTR
                var x = exonStart < start ? 0 : (exonStart - start) * xScale;
                var exonWidth = exonEnd > end ? width - x : (exonEnd - start) * xScale - x;

                ctx.fillStyle = "#000080";
                ctx.fillRect(x, height / 4, exonWidth, height / 2);
              } else {
                // This exon is both UTR and exon
                var _x = exonStart < start ? 0 : (exonStart - start) * xScale;
                var utrWidth = (cdsStart - start) * xScale - _x;
                var _exonWidth = exonEnd > end ? width - (_x + utrWidth) : (exonEnd - cdsStart) * xScale;

                ctx.fillStyle = "#000080";
                ctx.fillRect(_x, height / 4, utrWidth, height / 2);
                ctx.fillRect(_x + utrWidth, 0, _exonWidth, height);
              }
            } else if (exonEnd >= cdsEnd) {
              if (exonStart >= cdsEnd) {
                // The whole exon is in UTR
                var _x2 = exonStart < start ? 0 : (exonStart - start) * xScale;
                var _exonWidth2 = exonEnd > end ? width - _x2 : (exonEnd - start) * xScale - _x2;

                ctx.fillStyle = "#000080";
                ctx.fillRect(_x2, height / 4, _exonWidth2, height / 2);
              } else {
                // This exon is both UTR and exon
                var _x3 = exonStart < start ? 0 : (exonStart - start) * xScale;
                var _exonWidth3 = (cdsEnd - exonStart) * xScale;
                var _utrWidth = (exonEnd - cdsEnd) * xScale;

                ctx.fillStyle = "#000080";
                ctx.fillRect(_x3, 0, _exonWidth3, height);
                ctx.fillRect(_x3 + _exonWidth3, height / 4, _utrWidth, height / 2);
              }
            } else {
              // It is all exoninc
              var _x4 = exonStart < start ? 0 : (exonStart - start) * xScale;
              var _exonWidth4 = exonEnd > end ? width - _x4 : (exonEnd - start) * xScale - _x4;

              ctx.fillStyle = "#000080";
              ctx.fillRect(_x4, 0, _exonWidth4, height);
            }
          }
        }
      }
    }
  }, {
    key: 'showGeneDetails',
    value: function showGeneDetails(event) {
      alert(event.target.title);
    }
  }, {
    key: 'render',
    value: function render() {
      var canvasHeight = 20;
      return React.createElement(
        'div',
        { ref: 'thatDiv', style: { width: '100%' } },
        React.createElement('canvas', {
          ref: 'thatCanvas',
          onClick: this.showGeneDetails,
          'data-toggle': 'tooltip',
          title: this.props.name
        })
      );
    }
  }]);

  return Gene;
}(React.Component);

Gene.propTypes = {
  genomicRange: React.PropTypes.string.isRequired,
  accession_number: React.PropTypes.string.isRequired,
  chrom: React.PropTypes.string.isRequired,
  strand: React.PropTypes.string,
  txStart: React.PropTypes.number.isRequired,
  txEnd: React.PropTypes.number.isRequired,
  cdsStart: React.PropTypes.number.isRequired,
  cdsEnd: React.PropTypes.number.isRequired,
  exonStarts: React.PropTypes.arrayOf(React.PropTypes.number).isRequired,
  exonEnds: React.PropTypes.arrayOf(React.PropTypes.number).isRequired,
  name: React.PropTypes.string
};

var GeneTrack = function (_React$Component4) {
  _inherits(GeneTrack, _React$Component4);

  function GeneTrack(props) {
    _classCallCheck(this, GeneTrack);

    var _this4 = _possibleConstructorReturn(this, Object.getPrototypeOf(GeneTrack).call(this, props));

    _this4.state = {
      genes: []
    };

    _this4.fetchData = _this4.fetchData.bind(_this4);
    _this4.addBackground = _this4.addBackground.bind(_this4);
    return _this4;
  }

  _createClass(GeneTrack, [{
    key: 'componentDidMount',
    value: function componentDidMount() {
      this.fetchData(this.props.genomicRange);
      this.addBackground();
    }
  }, {
    key: 'componentWillReceiveProps',
    value: function componentWillReceiveProps(nextProps) {
      if (nextProps.hasOwnProperty('genomicRange') && nextProps.genomicRange !== this.props.genomicRange) {
        this.fetchData(nextProps.genomicRange);
      }
    }
  }, {
    key: 'fetchData',
    value: function fetchData(genomicRange) {
      var pattern = /(^chr|^Chr|^CHR|^)([0-9]|[1][0-9]|[2][0-2]|[xXyYmM]):([0-9, ]+)-([0-9, ]+)/;
      var table = 'refFlat';

      if (pattern.test(genomicRange)) {
        $.ajax(this.props.dataURL + '?genomic_range=' + genomicRange + '&table=' + table, {
          method: "GET",
          dataType: 'json',
          success: function (data) {
            this.setState({
              title: table,
              genes: data
            });
          }.bind(this),
          error: function error(_error) {
            console.error(_error);
          }
        });
      }
    }

    // This create the images used as backgroung for Gene following strand direction.

  }, {
    key: 'addBackground',
    value: function addBackground() {
      var forwardCanvas = this.refs.forwardBackgroundCanvas;
      var reverseCanvas = this.refs.reverseBackgroundCanvas;

      if (forwardCanvas) {
        var ctx = forwardCanvas.getDOMNode().getContext('2d');
        ctx.strokeStyle = "navy";
        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.lineTo(5, 2.5);
        ctx.lineTo(0, 5);
        ctx.stroke();
      } else {
        console.error('forwardCanvas is missing');
      }

      if (reverseCanvas) {
        var _ctx = reverseCanvas.getDOMNode().getContext('2d');
        _ctx.strokeStyle = "navy";
        _ctx.beginPath();
        _ctx.moveTo(5, 0);
        _ctx.lineTo(0, 2.5);
        _ctx.lineTo(5, 5);
        _ctx.stroke();
      } else {
        console.error('reverseCanvas is missing');
      }
    }
  }, {
    key: 'render',
    value: function render() {
      var genomicRange = this.props.genomicRange;

      // Thightly coupled with the UCSC knownGene table columns.
      var genes = this.state.genes.map(function (g) {
        var accession_number = g.name;
        var chrom = g.chrom;
        var strand = g.strand;
        var txStart = parseInt(g.txStart);
        var txEnd = parseInt(g.txEnd);
        var cdsStart = parseInt(g.cdsStart);
        var cdsEnd = parseInt(g.cdsEnd);
        var exonStarts = g.exonStarts.split(',').map(function (e) {
          return parseInt(e);
        });
        var exonEnds = g.exonEnds.split(',').map(function (e) {
          return parseInt(e);
        });
        var name = g.geneName;
        return React.createElement(Gene, {
          genomicRange: genomicRange,
          accession_number: accession_number,
          chrom: chrom,
          strand: strand,
          txStart: txStart,
          txEnd: txEnd,
          cdsStart: cdsStart,
          cdsEnd: cdsEnd,
          exonStarts: exonStarts,
          exonEnds: exonEnds,
          name: name
        });
      });

      var yAxisItems = this.state.genes.map(function (g) {
        return React.createElement(
          'div',
          { className: 'yAxis-geneName' },
          React.createElement(
            'span',
            null,
            g.geneName
          )
        );
      });

      var yAxis = React.createElement(
        'div',
        { className: 'geneNames' },
        yAxisItems
      );

      // TODO :: Put the yAxis as children (change prototype and render method)
      return React.createElement(
        Track,
        { title: 'Genes', yAxis: yAxis },
        React.createElement('canvas', { id: 'forwardBackground', ref: 'forwardBackgroundCanvas', width: '10', height: '5', style: { display: "none" } }),
        React.createElement('canvas', { id: 'reverseBackground', ref: 'reverseBackgroundCanvas', width: '10', height: '5', style: { display: "none" } }),
        genes
      );
    }
  }]);

  return GeneTrack;
}(React.Component);

GeneTrack.propTypes = {
  dataURL: React.PropTypes.string,
  genomicRange: React.PropTypes.string
};

GeneTrack.defaultProps = {
  dataURL: loris.BaseURL + "/genomic_viewer/ajax/getUCSCGenes.php"
};

var BetaValueDistribution = function (_React$Component5) {
  _inherits(BetaValueDistribution, _React$Component5);

  function BetaValueDistribution(props) {
    _classCallCheck(this, BetaValueDistribution);

    var _this5 = _possibleConstructorReturn(this, Object.getPrototypeOf(BetaValueDistribution).call(this, props));

    _this5.drawBox = _this5.drawBox.bind(_this5);
    _this5.iqr = _this5.iqr.bind(_this5);
    _this5.onClick = _this5.onClick.bind(_this5);
    return _this5;
  }

  _createClass(BetaValueDistribution, [{
    key: 'componentDidMount',
    value: function componentDidMount() {
      this.drawBox();
    }
  }, {
    key: 'componentWillReceiveProps',
    value: function componentWillReceiveProps(nextProps) {
      this.drawBox();
    }
  }, {
    key: 'drawBox',
    value: function drawBox() {
      // Drawing the boxplot using d3 library
      var margin = { top: 10, right: 0, bottom: 10, left: 0 };
      var boxWidth = 15;

      var boxPlot = d3.box().whiskers(this.iqr(1.5)).width(boxWidth).height(100);

      boxPlot.domain([0, 1]);

      // Binding data the the svg element group
      var g = d3.select('#' + this.props.cpgName).data([this.props.betaValues]);

      // Generating the boxplot
      g.call(boxPlot);

      // Moving the boxplot according to display scale
      g.attr("transform", "translate(" + (this.props.x - boxWidth / 2) + ", " + margin.top + ")");
    }

    // Returns a function to compute the interquartile range.

  }, {
    key: 'iqr',
    value: function iqr(k) {
      return function (d, i) {
        var q1 = d.quartiles[0],
            q3 = d.quartiles[2],
            iqr = (q3 - q1) * k,
            i = -1,
            j = d.length;
        while (d[++i] < q1 - iqr) {}
        while (d[--j] > q3 + iqr) {}
        return [i, j];
      };
    }
  }, {
    key: 'onClick',
    value: function onClick(event) {
      alert(event.target.parentElement.children[0].textContent);
    }
  }, {
    key: 'render',
    value: function render() {
      return React.createElement(
        'g',
        { id: this.props.cpgName, ref: this.props.cpgName, className: 'box', 'data-toggle': 'tooltip', onClick: this.onClick },
        React.createElement(
          'title',
          null,
          this.props.cpgName
        )
      );
    }
  }]);

  return BetaValueDistribution;
}(React.Component);

BetaValueDistribution.propTypes = {
  cpgName: React.PropTypes.string.isRequired,
  x: React.PropTypes.number,
  betaValues: React.PropTypes.arrayOf(React.PropTypes.number).isRequired
};

BetaValueDistribution.defaultProps = {
  x: 0
};

var CPGTrack = function (_React$Component6) {
  _inherits(CPGTrack, _React$Component6);

  function CPGTrack(props) {
    _classCallCheck(this, CPGTrack);

    var _this6 = _possibleConstructorReturn(this, Object.getPrototypeOf(CPGTrack).call(this, props));

    _this6.state = {
      data: []
    };

    _this6.fetchData = _this6.fetchData.bind(_this6);
    _this6.adjustLines = _this6.adjustLines.bind(_this6);
    return _this6;
  }

  _createClass(CPGTrack, [{
    key: 'componentDidMount',
    value: function componentDidMount() {
      this.adjustLines();
      this.fetchData(this.props.genomicRange);
    }
  }, {
    key: 'componentWillReceiveProps',
    value: function componentWillReceiveProps(nextProps) {
      if (nextProps.hasOwnProperty('genomicRange') && nextProps.genomicRange !== this.props.genomicRange) {
        this.fetchData(nextProps.genomicRange);
      }
    }
  }, {
    key: 'fetchData',
    value: function fetchData(genomicRange) {
      var _this7 = this;

      var pattern = /(^chr|^Chr|^CHR|^)([0-9]|[1][0-9]|[2][0-2]|[xXyYmM]):([0-9, ]+)-([0-9, ]+)/;

      if (pattern.test(genomicRange)) {
        (function () {
          // calculate the scale for the X axis
          var _genomicRange$match = genomicRange.match(pattern);

          var _genomicRange$match2 = _slicedToArray(_genomicRange$match, 5);

          var wholeString = _genomicRange$match2[0];
          var prefix = _genomicRange$match2[1];
          var chromosome = _genomicRange$match2[2];
          var start = _genomicRange$match2[3];
          var end = _genomicRange$match2[4];

          var width = _this7.refs.thatDiv.getDOMNode().clientWidth;
          var xScale = width / (parseInt(end) - parseInt(start));

          $.ajax(_this7.props.dataURL + '?genomic_range=' + genomicRange, {
            method: "GET",
            dataType: 'json',
            success: function (data) {
              data.forEach(function (d) {
                // calculate the coresponding X for each location
                d.x = xScale * (parseInt(d.genomic_location) - parseInt(start));
              }, this);
              this.setState({
                isLoaded: true,
                data: data
              });
            }.bind(_this7),
            error: function error(_error2) {
              console.error(_error2);
            }
          });
        })();
      }
    }
  }, {
    key: 'adjustLines',
    value: function adjustLines() {
      var width = this.refs.thatDiv.getDOMNode().clientWidth;
      var hypo = this.refs.hypo.getDOMNode();
      var hyper = this.refs.hyper.getDOMNode();
      var yAxis = this.refs.yAxis.getDOMNode();

      hypo.setAttribute("x2", width);
      hypo.setAttribute("transform", "translate(0,10)");

      hyper.setAttribute("x2", width);
      hyper.setAttribute("transform", "translate(0,10)");

      yAxis.setAttribute("transform", "translate(0,10)");
    }
  }, {
    key: 'render',
    value: function render() {
      var yAxisStyle = {
        stroke: "black"
      };
      var yAxis = React.createElement(
        'svg',
        { width: '40px', height: '120' },
        React.createElement(
          'g',
          { ref: 'yAxis' },
          React.createElement('line', { x1: '25', y1: '0', x2: '25', y2: '100', style: yAxisStyle }),
          React.createElement(
            'text',
            { x: '1', y: '40', dy: '0.3em' },
            '0.6'
          ),
          React.createElement(
            'text',
            { x: '1', y: '80', dy: '0.3em' },
            '0.2'
          ),
          React.createElement('line', { x1: '25', y1: '40', x2: '30', y2: '40', style: yAxisStyle }),
          React.createElement('line', { x1: '25', y1: '80', x2: '30', y2: '80', style: yAxisStyle })
        )
      );
      var lines = [React.createElement('line', { ref: 'hypo', x1: '0', y1: '80', x2: '0', y2: '80' }), React.createElement('line', { ref: 'hyper', x1: '0', y1: '40', x2: '0', y2: '40' })];

      var boxPlots = this.state.data.map(function (d) {
        var ref = 'cpg-' + d.cpg_name;
        return React.createElement(BetaValueDistribution, { ref: ref, cpgName: d.cpg_name, x: d.x, betaValues: d.beta_values });
      }, this);
      return React.createElement(
        Track,
        {
          title: 'Methylation 450k',
          yAxis: yAxis },
        React.createElement(
          'div',
          { className: 'Methylation-450k-chart', ref: 'thatDiv' },
          React.createElement(
            'svg',
            { width: '100%', height: '120', className: 'boxes' },
            boxPlots,
            lines
          )
        )
      );
    }
  }]);

  return CPGTrack;
}(React.Component);

CPGTrack.defaultProps = {
  dataURL: loris.BaseURL + "/genomic_viewer/ajax/getCPG.php"
};

var SNPTrack = function (_React$Component7) {
  _inherits(SNPTrack, _React$Component7);

  function SNPTrack(props) {
    _classCallCheck(this, SNPTrack);

    var _this8 = _possibleConstructorReturn(this, Object.getPrototypeOf(SNPTrack).call(this, props));

    _this8.state = {
      data: []
    };

    _this8.fetchData = _this8.fetchData.bind(_this8);
    _this8.onClick = _this8.onClick.bind(_this8);
    return _this8;
  }

  _createClass(SNPTrack, [{
    key: 'componentDidMount',
    value: function componentDidMount() {
      this.fetchData(this.props.genomicRange);
    }
  }, {
    key: 'componentWillReceiveProps',
    value: function componentWillReceiveProps(nextProps) {
      if (nextProps.hasOwnProperty('genomicRange') && nextProps.genomicRange !== this.props.genomicRange) {
        this.fetchData(nextProps.genomicRange);
      }
    }
  }, {
    key: 'fetchData',
    value: function fetchData(genomicRange) {
      var _this9 = this;

      var pattern = /(^chr|^Chr|^CHR|^)([0-9]|[1][0-9]|[2][0-2]|[xXyYmM]):([0-9, ]+)-([0-9, ]+)/;

      if (pattern.test(genomicRange)) {
        (function () {
          // calculate the scale for the X axis
          var _genomicRange$match3 = genomicRange.match(pattern);

          var _genomicRange$match4 = _slicedToArray(_genomicRange$match3, 5);

          var wholeString = _genomicRange$match4[0];
          var prefix = _genomicRange$match4[1];
          var chromosome = _genomicRange$match4[2];
          var start = _genomicRange$match4[3];
          var end = _genomicRange$match4[4];

          var width = _this9.refs.thatDiv.getDOMNode().clientWidth;
          var xScale = width / (parseInt(end) - parseInt(start));

          $.ajax(_this9.props.dataURL + '?genomic_range=' + genomicRange, {
            method: "GET",
            dataType: 'json',
            success: function (data) {
              data.forEach(function (d) {
                // calculate the coresponding X for each location
                d.x = xScale * (parseInt(d.genomic_location) - parseInt(start));
              }, this);
              this.setState({
                isLoaded: true,
                data: data
              });
            }.bind(_this9),
            error: function error(_error3) {
              console.error(_error3);
            }
          });
        })();
      }
    }
  }, {
    key: 'onClick',
    value: function onClick(event) {
      alert(event.target.textContent);
    }
  }, {
    key: 'render',
    value: function render() {
      var snps = this.state.data.map(function (s) {

        var className = void 0;

        console.log(s);
        return React.createElement(
          'rect',
          {
            className: className,
            x: s.x,
            y: '5',
            width: '5',
            height: '10',
            rx: '2',
            ry: '2',
            onClick: this.onClick
          },
          React.createElement(
            'title',
            null,
            s.rsID
          )
        );
      }, this);
      return React.createElement(
        Track,
        { title: 'SNP' },
        React.createElement(
          'div',
          { className: 'snp-chart', ref: 'thatDiv' },
          React.createElement(
            'svg',
            { width: '100%', height: '15', className: 'snps' },
            snps
          )
        )
      );
    }
  }]);

  return SNPTrack;
}(React.Component);

SNPTrack.defaultProps = {
  dataURL: loris.BaseURL + "/genomic_viewer/ajax/getSNP.php"
};

var ChIPPeakTrack = function (_React$Component8) {
  _inherits(ChIPPeakTrack, _React$Component8);

  function ChIPPeakTrack() {
    _classCallCheck(this, ChIPPeakTrack);

    return _possibleConstructorReturn(this, Object.getPrototypeOf(ChIPPeakTrack).apply(this, arguments));
  }

  _createClass(ChIPPeakTrack, [{
    key: 'render',
    value: function render() {
      return React.createElement('div', null);
    }
  }]);

  return ChIPPeakTrack;
}(React.Component);

/* exported GenomicViewerApp */

/**
 * Genomic viewer tool
 *
 * Serves as an browser for genomic data.
 *
 * @author Xavier Lecours Boucher
 * @version 1.0.0
 *
 * */


var GenomicViewerApp = function (_React$Component9) {
  _inherits(GenomicViewerApp, _React$Component9);

  function GenomicViewerApp(props) {
    _classCallCheck(this, GenomicViewerApp);

    var _this11 = _possibleConstructorReturn(this, Object.getPrototypeOf(GenomicViewerApp).call(this, props));

    _this11.state = {
      // Create a default genomic range to show 
      genomicRange: null
    };

    // Bind component instance to custom methods
    _this11.setGenomicRange = _this11.setGenomicRange.bind(_this11);
    return _this11;
  }

  /**
   * Sets a new Genomic Range
   *
   * @param {GenomicRange} genomicRange - the new genomic range
   *
   * @note This function will try to construct a genomicRange if a string is received.
   */


  _createClass(GenomicViewerApp, [{
    key: 'setGenomicRange',
    value: function setGenomicRange(genomicRange) {
      this.setState({ genomicRange: genomicRange });
    }
  }, {
    key: 'render',
    value: function render() {

      // Defining element names here ensures that `name` and `ref`
      // properties of the element are always kept in sync
      var controlPanel = "controlPanel";
      var genomicRange = this.state.genomicRange;

      // Create control panel and the tracks according to state

      // TODO:: Alex tells me that table are evil. (suggestion: flex-box)
      return React.createElement(
        'table',
        { className: 'col-md-12' },
        React.createElement(
          'tbody',
          null,
          React.createElement(
            'tr',
            null,
            React.createElement(
              'th',
              { className: 'col-md-2' },
              'chrY:15010000-15040000'
            ),
            React.createElement('th', { className: 'col-md-10' })
          ),
          React.createElement(
            'tr',
            null,
            React.createElement(
              'td',
              { colSpan: '2' },
              React.createElement(ControlPanel, { ref: controlPanel, genomicRange: genomicRange, setGenomicRange: this.setGenomicRange })
            )
          ),
          React.createElement(GeneTrack, { genomicRange: genomicRange }),
          React.createElement(CPGTrack, { genomicRange: genomicRange }),
          React.createElement(SNPTrack, { genomicRange: genomicRange }),
          React.createElement(ChIPPeakTrack, null)
        )
      );
    }
  }]);

  return GenomicViewerApp;
}(React.Component);

/**
 * Render genomic_viewer_app on page load
 */


window.onload = function () {
  var viewer = React.createElement(GenomicViewerApp, null);

  // Create a wrapper div in which react component will be loaded
  var genomicViewerDOM = document.createElement('div');
  genomicViewerDOM.id = 'page-genomic-viewer';

  // Append wrapper div to page content
  var rootDOM = document.getElementById("lorisworkspace");
  rootDOM.appendChild(genomicViewerDOM);

  React.render(viewer, document.getElementById("page-genomic-viewer"));
};