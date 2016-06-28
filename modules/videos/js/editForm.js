/**
 * Video Upload Form
 *
 * Fetches data from Loris backend and display a form allowing
 * to upload a video attached to a specific instrument
 *
 * @author Alex Ilea
 * @version 1.0.0
 *
 * */
var VideoUploadForm = React.createClass({
  displayName: 'VideoUploadForm',


  propTypes: {
    DataURL: React.PropTypes.string.isRequired
  },

  getInitialState: function () {
    return {
      'formData': {},
      'uploadResult': null,
      'Headers': [],
      'Data': [],
      'isLoaded': false,
      'loadedData': 0
    };
  },

  componentDidMount: function () {
    var that = this;
    $.ajax(this.props.DataURL, {
      dataType: 'json',
      xhr: function () {
        var xhr = new window.XMLHttpRequest();
        xhr.addEventListener("progress", function (evt) {
          that.setState({
            'loadedData': evt.loaded
          });
        });
        return xhr;
      },
      success: function (data) {

        var formData = {
          'idVideo': data.videoData.id,
          'for_site': data.videoData.for_site,
          'date_taken': data.videoData.date_taken,
          'comments': data.videoData.comments,
          'hide_video': data.videoData.hide_video
        };

        that.setState({
          'Data': data,
          'isLoaded': true,
          'videoData': data.videoData,
          'formData': formData
        });
      },
      error: function (data, error_code, error_msg) {
        console.error(error_code + ': ' + error_msg);
        that.setState({ "error": "Error loading data" });
      }
    });
  },

  handleSubmit: function (e) {
    e.preventDefault();

    var self = this;
    var myFormData = this.state.formData;
    var formRefs = this.refs;
    var formData = new FormData();
    var hasErrors = false;

    for (var key in myFormData) {
      formData.append(key, myFormData[key]);
    }

    // // Error checking
    // Object.keys(formRefs).map(function(ref) {
    //   if (formRefs[ref].state && formRefs[ref].state.value == "") {
    //     formRefs[ref].state.hasError = true;
    //     hasErrors = true;
    //   }
    // });
    // this.forceUpdate();
    // if (hasErrors) { return; }

    $('#videoUploadEl').hide();
    $("#file-progress").removeClass('hide');

    $.ajax({
      type: 'POST',
      url: loris.BaseURL + "/videos/ajax/VideoUpload.php?action=edit",
      data: formData,
      cache: false,
      contentType: false,
      processData: false,
      xhr: function () {
        var xhr = new window.XMLHttpRequest();
        xhr.upload.addEventListener("progress", function (evt) {
          if (evt.lengthComputable) {
            var progressbar = $("#progressbar");
            var progresslabel = $("#progresslabel");
            var percent = Math.round(evt.loaded / evt.total * 100);
            $(progressbar).width(percent + "%");
            $(progresslabel).html(percent + "%");
            progressbar.attr('aria-valuenow', percent);
          }
        }, false);
        return xhr;
      },
      success: function (data) {
        $("#file-progress").addClass('hide');
        self.setState({
          uploadResult: "success"
        });
        self.showAlertMessage();
      },
      error: function (err) {
        console.error(err);
        self.setState({
          uploadResult: "error"
        });
        self.showAlertMessage();
      }

    });
  },

  setFormData: function (formElement, value) {
    var formData = this.state.formData;
    formData[formElement] = value;

    this.setState({
      formData: formData
    });
  },

  showAlertMessage: function () {
    var self = this;

    if (this.refs["alert-message"] == null) {
      return;
    }

    var alertMsg = this.refs["alert-message"].getDOMNode();
    $(alertMsg).fadeTo(2000, 500).delay(3000).slideUp(500, function () {
      self.setState({
        uploadResult: null
      });
    });
  },

  render: function () {

    if (!this.state.isLoaded) {

      if (this.state.error != undefined) {
        return React.createElement(
          'div',
          { className: 'alert alert-danger' },
          React.createElement(
            'strong',
            null,
            this.state.error
          )
        );
      }

      return React.createElement(
        'button',
        { className: 'btn-info has-spinner' },
        'Loading ',
        React.createElement('span', {
          className: 'glyphicon glyphicon-refresh glyphicon-refresh-animate' })
      );
    }

    var alertMessage = "";
    var alertClass = "alert text-center hide";

    if (this.state.uploadResult) {

      if (this.state.uploadResult == "success") {
        alertClass = "alert alert-success text-center";
        alertMessage = "Update Successful!";
      } else if (this.state.uploadResult == "error") {
        alertClass = "alert alert-danger text-center";
        alertMessage = "Failed to update the video";
      }
    }

    return React.createElement(
      'div',
      null,
      React.createElement(
        'div',
        { className: alertClass, role: 'alert', ref: 'alert-message' },
        alertMessage
      ),
      React.createElement(
        FormElement,
        {
          name: 'videoUpload',
          action: this.props.action,
          onSubmit: this.handleSubmit,
          ref: 'form'
        },
        React.createElement(
          'h3',
          null,
          'Edit Video'
        ),
        React.createElement('br', null),
        React.createElement(SelectElement, {
          name: 'pscid',
          label: 'PSCID',
          options: this.state.Data.candidates,
          onUserInput: this.setFormData,
          ref: 'pscid',
          required: true,
          disabled: true,
          value: this.state.videoData.pscid
        }),
        React.createElement(SelectElement, {
          name: 'visit_label',
          label: 'Visit Label',
          options: this.state.Data.visits,
          onUserInput: this.setFormData,
          ref: 'visit_label',
          required: true,
          disabled: true,
          value: this.state.videoData.visit_label
        }),
        React.createElement(SelectElement, {
          name: 'instrument',
          label: 'Instrument',
          options: this.state.Data.instruments,
          onUserInput: this.setFormData,
          ref: 'instrument',
          disabled: true,
          value: this.state.videoData.instrument
        }),
        React.createElement(SelectElement, {
          name: 'for_site',
          label: 'For Site',
          options: this.state.Data.sites,
          onUserInput: this.setFormData,
          ref: 'for_site',
          value: this.state.videoData.for_site
        }),
        React.createElement(DateElement, {
          name: 'date_taken',
          label: 'Date of Administration',
          minYear: '2000',
          maxYear: '2017',
          onUserInput: this.setFormData,
          ref: 'date_taken',
          value: this.state.videoData.date_taken
        }),
        React.createElement(TextareaElement, {
          name: 'comments',
          label: 'Comments',
          onUserInput: this.setFormData,
          ref: 'comments',
          value: this.state.videoData.comments
        }),
        React.createElement(FileElement, {
          id: 'videoUploadEl',
          onUserInput: this.setFormData,
          required: true,
          disabled: true,
          ref: 'file',
          label: 'Uploaded file',
          value: this.state.videoData.file_name
        }),
        React.createElement(SelectElement, {
          name: 'hide_video',
          label: 'Hide Video',
          emptyOption: false,
          options: ["No", "Yes"],
          onUserInput: this.setFormData,
          ref: 'hide_video',
          value: this.state.videoData.hide_video
        }),
        React.createElement(ButtonElement, { label: 'Update Video' })
      )
    );
  }
});

RVideoUploadForm = React.createFactory(VideoUploadForm);